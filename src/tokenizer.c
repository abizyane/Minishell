/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:17:46 by abizyane          #+#    #+#             */
/*   Updated: 2023/06/22 19:15:09 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	char_handler(t_token **head, char *line, int *i)
{
	int	j;

	j = 0;
	while (line[(*i) + j] && !is_whitespace(line[(*i) + j])
		&& !is_quotes(line[(*i) + j]) && !is_separator(line[(*i) + j]))
		j++;
	lstadd_token(head, ft_substr(line, (*i), j));
	(*i) += j;
}

int	quotes_handler(t_token **head, char *line, int *i)
{
	if (closed_quotes(line, (*i)))
		lstadd_token(head, ft_substr(line, (*i), (closed_quotes(line, (*i))
					- (*i) + 1)));
	else
		return ((int)write(2, RED"syntax error!"RST"\n", 25));
	(*i) = closed_quotes(line, (*i)) + 1;
	return (0);
}

void	separator_handler(t_token **head, char *line, int *i)
{
	if (line[(*i) + 1] == line[(*i)] && line[(*i)] != '|')
		lstadd_token(head, ft_substr(line, (*i)++, 2));
	else
		lstadd_token(head, ft_substr(line, (*i), 1));
	(*i)++;
}

void	whitespace_handler(t_token **head, char *line, int *i)
{
	lstadd_token(head, ft_substr(line, (*i)++, 1));
	while (is_whitespace(line[(*i)]))
		(*i)++;
}

t_token	*tokenizer(char *line)
{
	int		i;
	char	*arr;
	t_token	*head;

	i = 0;
	arr = ft_strtrim(line, " ");
	head = ft_calloc(sizeof(t_token), 1);
	while (arr[i])
	{
		if (is_whitespace(arr[i]))
			whitespace_handler(&head, arr, &i);
		else if (is_separator(arr[i]))
			separator_handler(&head, arr, &i);
		else if (is_quotes(arr[i]))
		{
			if (quotes_handler(&head, arr, &i))
				return (lstclear_tokens(&head), NULL);
		}
		else
			char_handler(&head, arr, &i);
	}
	if (check_tokens(&head))
		return (lstclear_tokens(&head), NULL);
	return (head);
}
