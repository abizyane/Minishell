/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 03:59:35 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/10 12:38:39 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_new(char *key, char *content)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->content = content;
	new->nxt = NULL;
	new->export_f = 0;
	new->p_flag = 0;
	return (new);
}

void	env_add_back(t_env **env_head, char	**env_var)
{
	t_env	*tmp;
	t_env	*new_env;

	tmp = *env_head;
	new_env = env_new(env_var[0], env_var[1]);
	if (!tmp)
		*(env_head) = new_env;
	else
	{
		while (tmp && tmp->nxt)
			tmp = tmp->nxt;
		tmp->nxt = new_env;
	}
}

t_env	*lst_env(char **env)
{
	int		i;
	t_env	*head;
	char	*str[2];
	int		check;

	i = 0;
	check = 0;
	head = env_new(NULL, NULL);
	while (env && env[i])
	{
		str[0] = ft_substr(env[i], 0, ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '=')));
		str[1] = ft_substr(ft_strchr(env[i], '='), 1, ft_strlen(env[i]));
		if (ft_strcmp(str[0], "PATH") == 0)
			check = 1;
		if (ft_strcmp(str[0], "OLDPWD") == 0)
		{
			free(str[0]);
			free(str[1]);
		}
		else
			env_add_back(&head, str);
		i++;
	}
	if (check == 0)
	{	
		str[0] = ft_strdup("PATH");
		str[1] = ft_strdup(_PATH_STDPATH);
		env_add_back(&head, str);
	}
	return (head);
}

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
