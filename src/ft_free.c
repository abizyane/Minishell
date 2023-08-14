/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:54:22 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/14 15:58:48 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_var(t_env *head, char *env_var)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, env_var) == 0)
			return (tmp->content);
		tmp = tmp->nxt;
	}
	return (NULL);
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = *env;
		*env = (*env)->nxt;
		free(tmp->key);
		free(tmp->content);
		free(tmp);
	}
	*env = NULL;
}

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
