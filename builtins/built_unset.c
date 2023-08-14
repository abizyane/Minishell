/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:27:16 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/14 07:24:21 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_unset_msg(char *key)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	ft_putstr_fd("\n", 2);
	g_data.exit_status = 1;
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
	next = (*env)->nxt;
	while (next && ft_strcmp(next->key, key) != 0)
	{
		tmp = tmp->nxt;
		next = tmp->nxt;
	}
	tmp->nxt = next->nxt;
	if (next && next->key)
		free(next->key);
	if (next && next->content)
		free(next->content);
	if (next)
		free(next);
}

int	unset(t_cmdline *cmd, t_env **env)
{
	t_env	*var;
	int		i;

	i = 1;
	g_data.exit_status = 0;
	if (!cmd->args[i] || !(*env))
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
	return (g_data.exit_status);
}
