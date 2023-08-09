/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:27:16 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/09 08:12:21 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_msg(char *key)
{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd("': not a valid identifier", 2);
		ft_putstr_fd("\n", 2);
		exit_status = 1;
}

int	check_syntax(char *key)
{
	int	i;

	i = 0;
	while (key[i])
	{
		if (i == 0 && !ft_isalpha(key[i]) && key[i] != '_')
			return (0);
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (i);
}

int unset(t_cmdline *cmd, t_env **env)
{
	t_env	*var;
    int     i;

    i = 1;
    exit_status = 0;
	if (!cmd->args[i])
        return (EXIT_SUCCESS);
    while (cmd->args[i])
    {
        if (!check_syntax(cmd->args[i]))
            print_msg(cmd->args[i]);
        var = find_env(*env, cmd->args[i]);
	    if (var)
        {
            //TODO: remove node ;
            //TODO: if the node is the head replace the head;
        
        }
        i++;
    }
    return (exit_status);
}