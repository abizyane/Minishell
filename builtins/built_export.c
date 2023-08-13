/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:27:02 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/10 10:06:25 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_p_flag(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp) 
	{
		tmp->p_flag = 0;
		tmp = tmp->nxt;
	}
}

void	print_list(t_env *env)
{
	t_env	*curr_env;
	t_env	*min;
	t_env	*check;

	curr_env = env;
	while (curr_env) 
	{
		min = NULL;
		check = env;
		while (check) 
		{
			if (!check->p_flag) 
				if (!min || ft_strcmp(check->key, min->key) < 0) 
					min = check;
			check = check->nxt;
		}
		if (min) 
		{
			if (min->content && min->key)
				printf("declare -x %s=\"%s\"\n", min->key, min->content);
			else if (min->key)
				printf("declare -x %s\n", min->key);
			min->p_flag = 1;
		}
		curr_env = curr_env->nxt;
	}
	reset_p_flag(env);
}

int	check_syntax(char *new_var)
{
	int	i;

	i = 0;
	while (new_var[i])
	{
		if (i == 0 && !ft_isalpha(new_var[i]) && new_var[i] != '_')
			return (0);
		if (!ft_isalnum(new_var[i]) && new_var[i] != '=' && new_var[i] != '_')
			return (0);
		if (new_var[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

void	update_var(t_env **env, char **new_var)
{
	t_env	*var;

	var = find_env(*env, new_var[0]);
	if (var->content && new_var[1])
	{
		freeptr(&var->content);
		var->content = new_var[1];
		return ;
	}
	else
	{
		if (new_var[1])
			var->content = new_var[1];
		else if (!new_var[1] && ft_strcmp(var->content, ""))
		{
			freeptr(&var->content);
			var->content = ft_strdup("");
		}
	}
}

void	add_var(t_env **env, char *new_var)
{
	t_env	*tmp;
	char	**str;
	int		i;
	int		j;

	tmp = (*env);
	i = check_syntax(new_var);
	if (!i)
		return ;
	str = ft_calloc(3, sizeof(char *));
	str[0] = ft_substr(new_var, 0, i);
	str[1] = NULL;
	j = ++i;
	while (new_var[j - 1] == '=' && new_var[i])
		i++;
	if (new_var[j - 1] == '=' && new_var[j])
		str[1] = ft_substr(new_var, j, i);
	tmp = find_env(*env, str[0]);
	if (tmp)
	{
		update_var(env, str);
		free (str[0]);
	}
	else
		env_add_back(env, str);
	free(str);
}

void	print_msg(char *key)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	ft_putstr_fd("\n", 2);
	g_exit_status = 1;
}

int	ft_export(t_cmdline *cmd, t_env **env)
{
	int	i;

	i = 1;
	if (!(*env))
		return (EXIT_FAILURE);
	if (!cmd->args[1])
	{
		print_list(*env);
		return (EXIT_SUCCESS);
	}
	while (cmd->args[i])
	{
		if (!check_syntax(cmd->args[i]))
			print_msg(cmd->args[i]);
		else
			add_var(env, cmd->args[i]);
		i++;
	}
	if (!cmd->args[i] && g_exit_status == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
