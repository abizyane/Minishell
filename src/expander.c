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

char	*replace_var(char *env_var, char *line, int start, t_env *env_head)
{
	char	*new_line;
	char	*value;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	value = find_var(env_head, env_var);
	new_line = ft_calloc((ft_strlen(value) + (ft_strlen(line) - ft_strlen(env_var))) + 1, sizeof(char));
	if (!new_line)
		return (NULL);
	while (line[i] && i < start)
		new_line[j++] = line[i++];
	if (value)
	{
		while (value[k])
			new_line[j++] = value[k++];
		i += (int) ft_strlen(env_var) + 1;
		while (line[i])
			new_line[j++] = line[i++];
	}
	else
	{
		while (line[++i] && env_var[k] && line[i] == env_var[k])
			k++;
		while (line[i])
			new_line[j++] = line[i++];
	}
	return (freeptr(&line), new_line);
}

char	*remove_ds(char *line, int start)
{
	char	*new_line;
	int		i;
	int		j;

	new_line = ft_calloc(ft_strlen(line) + 2, sizeof(char));
	i = 0;
	j = 0;
	while (i < start)
		new_line[i++] = line[j++];
	if (line[j + 1] == '?')
	{
		char	*var = ft_itoa(g_exit_status);
		int		k = 0;
		while (var[k])
			new_line[i++] = var[k++];
		free(var);
	}
	j += 2;
	while (line[j])
		new_line[i++] = line[j++];
	return (freeptr(&line), new_line);
}

void	expand_env_var(t_token **head, t_env *env)
{
	t_token	*token;
	char	*env_var;
	int		i;
	int		j;
	int		f = 0;

	token = (*head);
	while (token)
	{
		if (token->type == Word)
		{
			i = 0;
			while (token->line && token->line[i])
			{
				if (token->line && token->line[i] == '\'' && f == 0)
					i = closed_quotes(token->line, i) + 1;
				else if (token->line[i] == '$' && token->line[i + 1] && (ft_isalpha(token->line[i + 1]) || token->line[i + 1] == '_'))
				{
					j = 0;
					i++;
					while (token->line[i + j] && (ft_isalnum(token->line[i + j]) || token->line[i + j] == '_'))
						j++;
					env_var = ft_substr(token->line, i, j);
					if (!env_var || (token->prv && token->prv->type == Heredoc))
						continue ;
					token->line = replace_var(env_var, token->line, --i, env);
				}
				else if (token->line[i] == '$' && token->line[i + 1] && (ft_isdigit(token->line[i + 1]) || token->line[i + 1] == '?'))
					token->line = remove_ds(token->line, i);
				else
				{
					if (token->line && token->line[i] == '\"')
						f++;
					if (token->line && token->line[i] == '\"' && f == 2)
						f = 0;
					i++;
				}
			}
		}
		token = token->nxt;
	}
}

char	*expand_vars(char *line, t_env *env)
{
	char	*var;
	int		i;
	int		j;

	i = 0;
	var = NULL;
	while (line && line[i])
	{
		if (line[i] == '$' && line[i + 1] && (ft_isalpha(line[i + 1]) || line[i + 1] == '_'))
		{
			j = 0;
			i++;
			while (line[i + j] && (ft_isalnum(line[i + j]) || line[i + j] == '_'))
				j++;
			var = ft_substr(line, i, j);
			if (!var)
				continue ;
			line = replace_var(var, line, --i, env);
		}
		else if (line[i] == '$' && line[i + 1] && (ft_isdigit(line[i + 1]) || line[i + 1] == '?'))
			line = remove_ds(line, i);
		else
			i++;
	}
	return (line);
}
