/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 07:14:29 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/14 07:26:21 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	change_var(char **line, t_env *env, t_tmp vars)
{
	*line = replace_var(vars.var, *line, --vars.i, env);
	free(vars.var);
	return ;
}

char	*expand_vars(char *line, t_env *env)
{
	t_tmp	vars;

	init_var(&vars);
	while (line && line[vars.i])
	{
		if (line[vars.i] == '$' && line[vars.i + 1] 
			&& (ft_isalpha(line[vars.i + 1]) || line[vars.i + 1] == '_'))
		{
			vars.j = 0;
			vars.i++;
			while (line[vars.i + vars.j] && (ft_isalnum(line[vars.i + vars.j])
					|| line[vars.i + vars.j] == '_'))
				vars.j++;
			vars.var = ft_substr(line, vars.i, vars.j);
			if (!vars.var)
				continue ;
			change_var(&line, env, vars);
		}
		else if (line[vars.i] == '$' && line[vars.i + 1]
			&& (ft_isdigit(line[vars.i + 1]) || line[vars.i + 1] == '?'))
			line = remove_ds(line, vars.i);
		else
			vars.i++;
	}
	return (line);
}

void	init_var(t_tmp *vars)
{
	ft_bzero(vars, sizeof(t_tmp));
	return ;
}

char	*replace_var(char *env_var, char *line, int start, t_env *env_head)
{
	t_tmp	vars;

	init_var(&vars);
	vars.value = find_var(env_head, env_var);
	vars.new_line = ft_calloc((ft_strlen(vars.value) + (ft_strlen(line)
					- ft_strlen(env_var))) + 1, sizeof(char));
	while (line[vars.i] && vars.i < start)
		vars.new_line[vars.j++] = line[vars.i++];
	if (vars.value)
	{
		while (vars.value[vars.k])
			vars.new_line[vars.j++] = vars.value[vars.k++];
		vars.i += (int)ft_strlen(env_var) + 1;
		while (line[vars.i])
			vars.new_line[vars.j++] = line[vars.i++];
	}
	else
	{
		while (line[++vars.i] && env_var[vars.k]
			&& line[vars.i] == env_var[vars.k])
			vars.k++;
		while (line[vars.i])
			vars.new_line[vars.j++] = line[vars.i++];
	}
	return (freeptr(&line), vars.new_line);
}
