/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:24:23 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/11 20:13:20 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*lstnew_token(char *line)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	if (line)
		new->line = ft_strdup(line);
	new->nxt = NULL;
	new->prv = NULL;
	return (new);
}

t_token	*last_token(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	if (!head || !tmp->nxt)
		return (head);
	while (tmp->nxt)
		tmp = tmp->nxt;
	return (tmp);
}

void	lstadd_token(t_token **head, char *line)
{
	t_token	*new;
	t_token	*tmp;

	new = lstnew_token(line);
	tmp = *head;
	if (!tmp->line)
		(*head) = new;
	else
	{
		while (tmp && tmp->nxt)
			tmp = tmp->nxt;
		tmp->nxt = new;
		new->prv = tmp;
	}
}

void	lstclear_tokens(t_token **head)
{
	t_token	*tmp;
	t_token	*next;

	tmp = (*head);
	while (tmp)
	{
		next = tmp->nxt;
		freeptr(&tmp->line);
		free(tmp);
		tmp = next;
	}
	(*head) = NULL;
}

t_redir	*lstnew_redir(t_token *token)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = token->type;
	redir->nxt = NULL;
	redir->heredoc_flag = 0;
	return (redir);
}
