/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:24:23 by abizyane          #+#    #+#             */
/*   Updated: 2023/06/22 17:14:52 by abizyane         ###   ########.fr       */
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
		new->line = line;
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
	while(tmp)
	{
		next = tmp->nxt;
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
	return (redir);
}

void	lstadd_redir(t_redir **head, t_token *token)
{
	t_redir	*new;
	t_redir	*tmp;

	new = lstnew_redir(token);
	tmp = *head;
	if (!tmp)
		(*head) = new;
	else
	{
		while (tmp && tmp->nxt)
			tmp = tmp->nxt;
		tmp->nxt = new;
	}
}

t_redir	*last_redir(t_redir *head)
{
	t_redir	*tmp;

	tmp = head;
	if (!head || !tmp->nxt)
		return (head);
	while (tmp->nxt)
		tmp = tmp->nxt;
	return (tmp);
}

t_cmdline	*lstnew_command(char *cmd, int size)
{
	t_cmdline	*command;

	command = ft_calloc(1, sizeof(t_cmdline));
	if (!command)
		return (NULL);
	command->nxt = NULL;
	command->prv = NULL;
	command->redir = NULL;
	command->args = NULL;
	command->out = 1;
	if (cmd)
	{
		command->args = ft_calloc(size, sizeof(char *));
		command->args[0] = cmd;
	}
	return (command);
}

t_cmdline	*last_command(t_cmdline *head)
{
	t_cmdline	*tmp;

	tmp = head;
	if (!tmp || !tmp->nxt)
		return (head);
	while (tmp && tmp->nxt)
		tmp = tmp->nxt;
	return (tmp);
}

void	lstadd_command(t_cmdline **head, char *cmd, int size)
{
	t_cmdline	*new;
	t_cmdline	*tmp;

	new = lstnew_command(cmd, size);
	tmp = *head;
	if (!tmp)
		(*head) = new;
	if (tmp && !tmp->args)
	{
		free(*head);
		*head = new;
	}
	else
	{
		tmp = last_command(*head);
		tmp->nxt = new;
		new->prv = tmp;
	}
}