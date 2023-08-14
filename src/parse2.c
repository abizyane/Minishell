/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:31:54 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/14 15:35:07 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_token *head)
{
	int	i;

	i = 0;
	if (head && head->nxt && head->type == Pipe)
		head = head->nxt;
	while (head && head->type != Pipe)
	{
		if (head->type == Arg || head->type == Cmd)
			i++;
		head = head->nxt;
	}
	return (i + 1);
}

void	add_redir_fname(t_cmdline **head, t_token *token)
{
	t_cmdline	*tmp;
	t_redir		*r_tmp;

	tmp = last_command(*head);
	r_tmp = last_redir(tmp->redir);
	r_tmp->filename = ft_strdup(token->line);
	if (token->prv && token->prv->type == Heredoc && token->s == 1)
		r_tmp->heredoc_flag = 1;
}

void	add_args(t_cmdline **head, t_token *token)
{
	t_cmdline	*tmp;
	int			i;

	tmp = last_command(*head);
	i = 0;
	if (!tmp->args)
		tmp->args = ft_calloc(sizeof(char *), count_args(token));
	while (tmp->args && tmp->args[i] != 0)
		i++;
	tmp->args[i] = ft_strdup(token->line);
}

void	add_redir(t_cmdline **head, t_token *token)
{
	t_cmdline	*tmp;

	tmp = last_command(*head);
	lstadd_redir(&tmp->redir, token);
}

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
