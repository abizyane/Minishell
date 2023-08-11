/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:59:25 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/09 17:58:01 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redir(t_redir **redir)
{
	t_redir	*tmp;

	while (*redir)
	{
		tmp = *redir;
		*redir = (*redir)->nxt;
		free(tmp->filename);
		free(tmp);
	}
	*redir = NULL;
}

void	free_cmd(t_cmdline **cmd)
{
	t_cmdline	*tmp;

	while (*cmd)
	{
		tmp = *cmd;
		*cmd = (*cmd)->nxt;
		if (tmp->path)
			free(tmp->path);
		if (tmp->args)
			free_arr(tmp->args);
		if (tmp->redir)
			free_redir(&tmp->redir);
		free(tmp);
	}
	*cmd = NULL;
}

void	free_tokens(t_token **token)
{
	t_token	*tmp;

	while (*token)
	{
		tmp = *token;
		*token = (*token)->nxt;
		if (tmp->line)
			free(tmp->line);
		free(tmp);
	}
	*token = NULL;
}
