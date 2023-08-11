/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 03:59:35 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/11 20:20:48 by ahamrad          ###   ########.fr       */
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

void	env_add_back(t_env **env_head, char **env_var)
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
	int			i;
	t_env		*head;
	char		**str;
	int			check;

	i = 0;
	check = 0;
	head = env_new(NULL, NULL);
	while (env && env[i])
	{
		str = ft_split(env[i], '=');
		if (str && ft_strcmp(str[0], "PATH") == 0)
			check = 1;
		env_add_back(&head, str);
		free(str);
		i++;
	}
	if (check == 0)
	{
		str = ft_calloc(sizeof(char *), 2);
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
