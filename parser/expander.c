/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:14:01 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/14 07:27:33 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_ds(char *line, int start)
{
	char	*new_line;
	int		i;
	int		j;
	char	*var;
	int		k;

	new_line = ft_calloc(ft_strlen(line) + 2, sizeof(char));
	i = 0;
	j = 0;
	while (i < start)
		new_line[i++] = line[j++];
	if (line[j + 1] == '?')
	{
		var = ft_itoa(g_data.exit_status);
		k = 0;
		while (var[k])
			new_line[i++] = var[k++];
		free(var);
	}
	j += 2;
	while (line[j])
		new_line[i++] = line[j++];
	return (freeptr(&line), new_line);
}

int	check_env_var(int *i, t_token *token, t_env *env)
{
	int		j;
	char	*env_var;

	j = 0;
	(*i)++;
	while (token->line[*i + j] && (ft_isalnum(token->line[*i + j])
			|| token->line[*i + j] == '_'))
		j++;
	env_var = ft_substr(token->line, *i, j);
	if (!env_var || (token->prv && token->prv->type == Heredoc))
		return (1);
	token->line = replace_var(env_var, token->line, --(*i), env);
	freeptr(&env_var);
	return (0);
}

void	check_and_expand(t_token *token, t_env *env, t_tmp vars)
{
	while (token->line && token->line[vars.i])
	{
		if (token->line && token->line[vars.i] == '\'' && vars.k == 0)
			vars.i = closed_quotes(token->line, vars.i) + 1;
		else if (token->line[vars.i] == '$' && token->line[vars.i + 1]
			&& (ft_isalpha(token->line[vars.i + 1]) || token->line[vars.i
					+ 1] == '_'))
		{
			if (check_env_var(&vars.i, token, env) == 1)
				continue ;
		}
		else if (token->line[vars.i] == '$' && token->line[vars.i + 1]
			&& (ft_isdigit(token->line[vars.i + 1]) || token->line[vars.i
					+ 1] == '?'))
			token->line = remove_ds(token->line, vars.i);
		else
		{
			if (token->line && token->line[vars.i] == '\"')
				vars.k++;
			if (token->line && token->line[vars.i] == '\"' && vars.k == 2)
				vars.k = 0;
			vars.i++;
		}
	}
}

void	expand_env_var(t_token **head, t_env *env)
{
	t_token	*token;
	t_tmp	vars;

	init_var(&vars);
	token = (*head);
	while (token)
	{
		if (token->type == Word)
		{
			vars.i = 0;
			check_and_expand(token, env, vars);
		}
		token = token->nxt;
	}
}
