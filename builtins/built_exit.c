/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:26:55 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/10 12:14:56 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned long long	ft_atol(const char *str)
{
	int					i;
	int					sgn;
	unsigned long long	rslt;

	i = 0;
	sgn = 1;
	rslt = 0;
	if (!str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sgn = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rslt = (10 * rslt) + (str[i] - '0');
		i++;
	}
	return (rslt * sgn);
}

int	ft_check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[0] == '+' || str[0] == '-')
			i++;
		else if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (1);
	}
	if (ft_atol(str) > 9223372036854775807)
		return (1);
	return (0);
}

int	ft_exit(t_cmdline *cmd, int f)
{
	unsigned long long	exit_st;

	if (array_len(cmd->args) > 2)
	{
		if (f == 1)
			printf("exit\n");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (!cmd->args[1])
		exit_st = g_exit_status;
	else if (cmd->args[1] && ft_check_digit(cmd->args[1]) == 0)
		exit_st = ft_atol(cmd->args[1]);
	if (f == 1)
		printf("exit\n");
	if (cmd->args[1] && ft_check_digit(cmd->args[1]) == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_st = 255;
	}
	exit(exit_st);
	return (0);
}
