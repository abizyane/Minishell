/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:27:16 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/09 10:06:06 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_unset_msg(char *key)
{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(key, 2);
		ft_putstr_fd("': not a valid identifier", 2);
		ft_putstr_fd("\n", 2);
		exit_status = 1;
}

int	check_unset_syntax(char *key)
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

void	clear_env(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*next;

	tmp = (*env);
	if (tmp->nxt)
		next = (*env)->nxt;
	if (key && tmp && ft_strcmp(key, tmp->key) == 0)
	{
		tmp->nxt = NULL;
		free(tmp->key);
		free(tmp->content);
		free(tmp);
		(*env) = next;
	}
	else
	{
		while(next && ft_strcmp(next->key, key) != 0)
		{
			tmp = tmp->nxt;
			next = tmp->nxt;
		}
		tmp->nxt = next->nxt;
		if (next->key)
			free(next->key);
		if (next->content)
			free(next->content);
		free(next);
	}
}

//TODO: unsetting the head causes abort

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
        if (!check_unset_syntax(cmd->args[i]))
            print_unset_msg(cmd->args[i]);
        var = find_env(*env, cmd->args[i]);
	    if (var)
			clear_env(env, var->key);
        i++;
    }
    return (exit_status);
}