/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:59:25 by abizyane          #+#    #+#             */
/*   Updated: 2023/07/15 18:59:25 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

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
	if (!head || !tmp->nxt)
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
	if (!(*head))
		(*head) = new;
	else
	{
		tmp = last_command(*head);
		tmp->nxt = new;
		new->prv = tmp;
	}
}
