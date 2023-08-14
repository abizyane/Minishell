/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 15:49:05 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/14 17:27:06 by abizyane         ###   ########.fr       */
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

void	check_min(t_env **check, t_env **min)
{
	while (*check)
	{
		if (!(*check)->p_flag)
			if (!(*min) || ft_strcmp((*check)->key, (*min)->key) < 0)
				*min = *check;
		*check = (*check)->nxt;
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
		check_min(&check, &min);
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
