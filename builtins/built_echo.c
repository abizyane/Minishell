/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:26:33 by ahamrad           #+#    #+#             */
/*   Updated: 2023/07/31 23:50:41 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		echo_option(char *arg)
{
	int i;
	int flag;
	
	i = 0;
	flag = 0;
	if (arg[i] != '-')
		return (flag);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		flag = 1;
	return (flag);
}

void	print_args(t_cmdline *cmd, int flag, int i)
{
	if (!cmd->args[i])
	{
		if (!flag)
			ft_putstr_fd("\n", STDOUT_FILENO);
		return ;
	}
	while (cmd->args[i] && cmd->args[i + 1])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!cmd->args[i + 1] && !flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

int		echo(t_cmdline *cmd)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	while (cmd->args[i] && echo_option(cmd->args[i]))
	{
		flag = 1;
		i++;
	}
	print_args(cmd, flag, i);
	return (0);
}
