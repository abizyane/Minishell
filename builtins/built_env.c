/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:26:47 by ahamrad           #+#    #+#             */
/*   Updated: 2024/07/01 17:05:00 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_cmdline *cmd, t_env *env)
{
	if (!cmd->args[1])
	{
		while (env)
		{
			if (env->content)
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
