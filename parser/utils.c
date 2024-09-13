/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:47:41 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/14 16:57:05 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**lst_to_arr(t_env *env)
{
	int		i;
	char	**arr;
	t_env	*tmp;
	char	*tmp2;

	i = 0;
	tmp = env;
	while (tmp && ++i)
		tmp = tmp->nxt;
	arr = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (env)
	{
		if (env->key)
		{
			tmp2 = ft_strjoin(env->key, "=");
			arr[i] = ft_strjoin(tmp2, env->content);
			free(tmp2);
			i++;
		}
		env = env->nxt;
	}
	arr[i] = NULL;
	return (arr);
}

char	**empty_env(void)
{
	char	**env;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	env = ft_calloc(4, sizeof(char *));
	env[0] = ft_strjoin("PWD=", cwd);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	if (env)
		freeptr(&cwd);
	return (env);
}
