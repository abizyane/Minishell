/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:43:31 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/06 19:44:29 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_type(t_token **head)
{
	t_token	*token;

	token = (*head);
	while (token)
	{
		if (ft_strncmp(token->line, "|", 1) == 0)
			token->type = Pipe;
		else if (ft_strncmp(token->line, "<<", 2) == 0)
			token->type = Heredoc;
		else if (ft_strncmp(token->line, ">>", 2) == 0)
			token->type = redApp;
		else if (ft_strncmp(token->line, "<", 1) == 0)
			token->type = redIn;
		else if (ft_strncmp(token->line, ">", 1) == 0)
			token->type = redOut;
		else if (is_whitespace(token->line[0]))
			token->type = Space;
		else
			token->type = Word;
		token = token->nxt;
	}
}

void	clean_list(t_token **head)
{
	t_token	*new_head;
	t_token	*tmp;

	get_type(head);
	new_head = ft_calloc(sizeof(t_token), 1);
	tmp = (*head);
	while (tmp)
	{
		if (tmp->prv && tmp->prv->type == Space)
			tmp->s = 1;
		if (tmp->type != Space)
			lstadd_token(&new_head, tmp->line);
		if (tmp->s == 1 || !tmp->prv)
			last_token(new_head)->s = 1;
		tmp = tmp->nxt;
	}
	lstclear_tokens(head);
	(*head) = new_head;
}

void	remove_quotes(t_token **token)
{
	t_token	*tmp;
	char	*new_line;
	char	c;
	int		i;
	int		j;

	tmp = (*token);
	while (tmp)
	{
		tmp->s = 0;
		if (tmp->type == Word && has_quates(tmp->line))
		{
			new_line = ft_calloc(sizeof(char), ft_strlen(tmp->line));
			i = 0;
			j = 0;
			while (tmp->line && tmp->line[i])
			{
				if (is_quotes(tmp->line[i]))
				{
					c = tmp->line[i++];
					while (tmp->line && tmp->line[i] && tmp->line[i] != c)
						new_line[j++] = tmp->line[i++];
				}
				else
					new_line[j++] = tmp->line[i];
				i++;
			}
			tmp->line = new_line;
			tmp->s = 1;
		}
		tmp = tmp->nxt;
	}
}

void	append_tokens(t_token **token)
{
	t_token	*tmp;
	t_token	*nxt_tmp;

	tmp = (*token);
	while (tmp)
	{
		if (tmp->nxt && tmp->type == Word && tmp->nxt->type == Word && tmp->nxt->s == 0)
		{
			tmp->line = ft_strjoin(tmp->line, tmp->nxt->line);
			nxt_tmp = tmp->nxt;
			if (tmp->nxt->nxt)
			{
				tmp->nxt->nxt->prv = tmp;
				tmp->nxt = tmp->nxt->nxt;
			}
			else
				tmp->nxt = NULL;
			freeptr(&nxt_tmp->line);
			free(nxt_tmp);
		}
		else
			tmp = tmp->nxt;

	}
}

int	check_tokens(t_token **head)
{
	t_token	*tmp;

	if (!(*head))
		return (1);
	clean_list(head);
	get_type(head);
	tmp = (*head);
	while (tmp)
	{
		if (!tmp->prv && tmp->type == Pipe)
			return ((int)write(2, RED "syntax error!" RST "\n", 25));
		if (!tmp->nxt && tmp->type != Word)
			return ((int)write(2, RED "syntax error!" RST "\n", 25));
		if (tmp->nxt && tmp->prv && tmp->type == Pipe && (tmp->prv->type != Word
				|| tmp->nxt->type == Pipe))
			return ((int)write(2, RED "syntax error!" RST "\n", 25));
		if (tmp->nxt && tmp->type != Word && tmp->type != Pipe
			&& tmp->nxt->type != Word)
			return ((int)write(2, RED "syntax error!" RST "\n", 25));
		tmp = tmp->nxt;
	}
	append_tokens(head);
	return (0);
}
