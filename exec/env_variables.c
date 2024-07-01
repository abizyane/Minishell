/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 03:59:35 by ahamrad           #+#    #+#             */
/*   Updated: 2024/07/01 17:02:22 by abizyane         ###   ########.fr       */
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

void	create_lst(char **env, t_env **head, int *check)
{
	int		i;
	char	*str[2];

	i = 0;
	while (env && env[i])
	{
		str[0] = ft_substr(env[i], 0, ft_strlen(env[i])
				- ft_strlen(ft_strchr(env[i], '=')));
		str[1] = ft_substr(ft_strchr(env[i], '='), 1, ft_strlen(env[i]));
		if (ft_strcmp(str[0], "PATH") == 0)
			*check = 1;
		if (ft_strcmp(str[0], "OLDPWD") == 0)
		{
			free(str[0]);
			free(str[1]);
		}
		else
			env_add_back(head, str);
		i++;
	}
}

t_env	*lst_env(char **env)
{
	t_env	*head;
	char	*str[2];
	int		check;

	check = 0;
	head = env_new(NULL, NULL);
	create_lst(env, &head, &check);
	if (check == 0)
	{
		str[0] = ft_strdup("PATH");
		str[1] = ft_strdup(_PATH_STDPATH);
		env_add_back(&head, str);
	}
	return (head);
}
