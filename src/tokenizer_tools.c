/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:00:52 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/09 18:02:43 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_whitespace(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}

int	is_separator(char c)
{
	if (c == '>' || c == '<')
		return (1);
	else if (c == '|')
		return (2);
	return (0);
}

int	is_quotes(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (2);
	return (0);
}

int	closed_quotes(char *str, int i) // returns the index of the other quote
{
	char	*tmp;
	char	c;
	int		j;

	tmp = str;
	c = str[i];
	j = i + 1;
	while (tmp[j])
	{
		if (tmp[j] == c)
			return (j);
		j++;
	}
	return (0);
}

int	has_quates(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_quotes(str[i]))
			return (1);
		i++;
	}
	return (0);
}
