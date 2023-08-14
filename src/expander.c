/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 17:14:01 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/10 06:24:57 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*init_expander(int ijk[3], char **new_line, char *env_var, t_env *env)
{
	char	*value;
	char	*line;

	line = *new_line;
	ft_bzero(ijk, sizeof(int) * 3);
	value = find_var(env, env_var);
	*new_line = ft_calloc((ft_strlen(value) + (ft_strlen(line) - \
		ft_strlen(env_var))) + 1, sizeof(char));
	return (value);
}

char	*replace_var(char *env_var, char *line, int start, t_env *env_head)
{
	char	*new_line;
	char	*value;
	int		ijk[3];

	new_line = line;
	value = init_expander(ijk, &new_line, env_var, env_head);
	while (line[ijk[0]] && ijk[0] < start)
		new_line[ijk[1]++] = line[ijk[0]++];
	if (value)
	{
		while (value[ijk[2]])
			new_line[ijk[1]++] = value[ijk[2]++];
		ijk[0] += (int) ft_strlen(env_var) + 1;
		while (line[ijk[0]])
			new_line[ijk[1]++] = line[ijk[0]++];
	}
	else
	{
		while (line[++ijk[0]] && env_var[ijk[2]]
				&& line[ijk[0]] == env_var[ijk[2]])
			ijk[2]++;
		while (line[ijk[0]])
			new_line[ijk[1]++] = line[ijk[0]++];
	}
	return (freeptr(&line), new_line);
}

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
		var = ft_itoa(g_exit_status);
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
	int	j;
	char	*env_var;

	j = 0;
	(*i)++;
	while (token->line[*i + j] && (ft_isalnum(token->line[*i + j]) \
		|| token->line[*i + j] == '_'))
		j++;
	env_var = ft_substr(token->line, *i, j);
	if (!env_var || (token->prv && token->prv->type == Heredoc))
		return 1;
	token->line = replace_var(env_var, token->line, --(*i), env);
	freeptr(&env_var);
	return (0);
}

void	check_and_expand(t_token *token, t_env *env, int *i)
{
	int	f;

	f = 0;
	if (token->line && token->line[*i] == '\'' && f == 0)
		*i = closed_quotes(token->line, *i) + 1;
	else if (token->line[*i] == '$' && token->line[*i + 1] 
			&& (ft_isalpha(token->line[*i + 1]) || token->line[*i + 1] == '_'))
	{
		if (check_env_var(i, token, env) == 1)
			return ;
	}
	else if (token->line[*i] == '$' && token->line[*i + 1] \
		&& (ft_isdigit(token->line[*i + 1]) || token->line[*i + 1] == '?'))
		token->line = remove_ds(token->line, *i);
	else
	{
		if (token->line && token->line[*i] == '\"')
			f++;
		if (token->line && token->line[*i] == '\"' && f == 2)
			f = 0;
		(*i)++;
	}
}

void	expand_env_var(t_token **head, t_env *env)
{
	t_token	*token;
	int		i;

	token = (*head);
	while (token)
	{
		if (token->type == Word)
		{
			i = 0;
			while (token->line && token->line[i])
				check_and_expand(token, env, &i);
		}
		token = token->nxt;
	}
}

int	norm(char **line, int *i, t_env	*env)
{
	char	*var;
	int		j;

	j = 0;
	(*i)++;
	while ((*line)[*i + j] && (ft_isalnum((*line)[*i + j]) || (*line)[*i + j] == '_'))
		j++;
	var = ft_substr(*line, *i, j);
	if (!var)
		return (1) ;
	*line = replace_var(var, *line, --(*i), env);
	free (var);
	return (0);
}

char	*expand_vars(char *line, t_env *env)
{
	int		i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '$' && line[i + 1] && (ft_isalpha(line[i + 1]) || line[i + 1] == '_'))
		{
			if (norm(&line, &i, env) == 1)
				continue;
		}
		else if (line[i] == '$' && line[i + 1] && (ft_isdigit(line[i + 1]) || line[i + 1] == '?'))
			line = remove_ds(line, i);
		else
			i++;
	}
	return (line);
}
