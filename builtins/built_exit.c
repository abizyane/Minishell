/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:26:55 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/07 19:07:07 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_digit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_exit(t_cmdline *cmd, int f)
{
	if (array_len(cmd->args) > 2)
	{
		if (f == 1)
			printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (!cmd->args[1])
	{
		if (f == 1)
			printf("exit\n");
		exit_status = 0; // to be replaced later
	}
	if (cmd->args[1] && ft_check_digit(cmd->args[1]) == 0)
	{
		exit_status = ft_atoi(cmd->args[1]);
		if (exit_status >= 256)
			exit_status = exit_status % 256;
		if (f == 1)
			printf("exit\n");
	}
	if (cmd->args[1] && (ft_check_digit(cmd->args[1]) == 1 || (ft_strlen(cmd->args[1]) >= 19 && cmd->args[1][18] > '7')))
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd->args[1]);
		exit_status = 255;
	}
	exit(exit_status); // to be replaced later
	return (0);
}
