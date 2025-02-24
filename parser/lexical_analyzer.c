/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyzer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 20:43:31 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/14 15:35:31 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_list(t_token **head)
{
	t_token	*new_head;
	t_token	*tmp;

	get_type(head);
	new_head = NULL;
	tmp = (*head);
	while (tmp)
	{
		if (tmp->prv && tmp->prv->type == Space)
			tmp->s = 1;
		if (tmp->type != Space)
			lstadd_token(&new_head, ft_strdup(tmp->line));
		if (tmp->s == 1 || !tmp->prv)
			last_token(new_head)->s = 1;
		tmp = tmp->nxt;
	}
	lstclear_tokens(head);
	(*head) = new_head;
}

void	handle_quotes(char *new_line, t_token *tmp)
{
	int		i;
	int		j;
	char	c;

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
}

void	remove_quotes(t_token **token)
{
	t_token	*tmp;
	char	*new_line;

	tmp = (*token);
	while (tmp)
	{
		tmp->s = 0;
		if (tmp->type == Word && has_quates(tmp->line))
		{
			new_line = ft_calloc(sizeof(char), ft_strlen(tmp->line));
			handle_quotes(new_line, tmp);
			freeptr(&tmp->line);
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
		if (tmp->nxt && tmp->type == Word && tmp->nxt->type == Word
			&& tmp->nxt->s == 0)
		{
			tmp->line = free_strjoin(tmp->line, tmp->nxt->line);
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

	clean_list(head);
	get_type(head);
	tmp = (*head);
	while (tmp)
	{
		if (!tmp->prv && tmp->type == Pipe)
			return ((int)write(2, "syntax error near unexpected token `|'\n",
					40));
		if (!tmp->nxt && tmp->type != Word)
			return ((int)write(2,
					"syntax error near unexpected token `newline'\n", 46));
		if (tmp->nxt && tmp->prv && tmp->type == Pipe && (tmp->prv->type != Word
				|| tmp->nxt->type == Pipe))
			return ((int)write(2, "syntax error near unexpected token `|'\n",
					40));
		if (tmp->nxt && tmp->type != Word && tmp->type != Pipe
			&& tmp->nxt->type != Word)
			return ((int)write(2,
					"syntax error near unexpected token `redirection'\n", 50));
		tmp = tmp->nxt;
	}
	append_tokens(head);
	return (0);
}
