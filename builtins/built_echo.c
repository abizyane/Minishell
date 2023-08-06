/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:26:33 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/06 11:15:48 by ahamrad          ###   ########.fr       */
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
	i++;
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
		printf("%s ", cmd->args[i]);
		i++; 
	}
	if (cmd->args[i])
		printf("%s", cmd->args[i]);
	if (!flag)
		printf("\n");
	return (0);
}
