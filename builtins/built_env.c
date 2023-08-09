/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:26:47 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/09 04:18:36 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(t_cmdline *cmd, t_env *env)
{
	int i;

	i = 0;
	if (!cmd->args[1])
	{
		while (env)
		{
			if (env->content && env->content[i])
				printf("%s=%s\n", env->key, env->content);
			env = env->nxt;
		}
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd("env: no options or arguments\n", 2);
		return (EXIT_FAILURE);
	}
}
