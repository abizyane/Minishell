/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 20:25:07 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/14 18:18:33 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_exit_status(int status)
{
	if (WIFEXITED(status))
		g_data.exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		g_data.exit_status = 128 + WTERMSIG(status);
		if (g_data.exit_status == 131)
			ft_putstr_fd("Quit: 3\n", 1);
	}
}

int	execute_builtin2(t_cmdline *cmd, t_env *env)
{
	if (cmd->args && !cmd->nxt && ft_check_builtin(cmd->args[0]) == 1)
	{
		execute_builtin(cmd, env, 1);
		g_data.rl = 0;
		return (1);
	}
	else
		return (0);
}

int	execute_builtin_redir(t_cmdline *cmd, t_env *env)
{
	if (cmd->args && !cmd->nxt && ft_check_builtin(cmd->args[0]) == 1
		&& cmd->redir)
	{
		exec_builtin_redir(cmd, env, 1);
		g_data.rl = 0;
		return (1);
	}
	else
		return (0);
}
