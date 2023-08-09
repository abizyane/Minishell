/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:26:33 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/08 23:50:04 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		echo_option(char *arg)
{
	int i;
	
	i = 0;
	if (!arg)
		return (1);
	if (arg[i] != '-')
		return (1);
	if (!arg[++i])
		return (1);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int		echo(t_cmdline *cmd)
{
	int i;
	int flag;

	i = 1;
	flag = 0;
	while (cmd->args[i] && echo_option(cmd->args[i]) == 0)
	{
		flag++;
		i++;
	}
	while (cmd->args[i] && cmd->args[i + 1])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		i++; 
	}
	if (cmd->args[i])
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
