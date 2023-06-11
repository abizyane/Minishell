/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:17:46 by abizyane          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/08/10 13:36:03 by abizyane         ###   ########.fr       */
=======
/*   Updated: 2023/06/10 20:26:26 by abizyane         ###   ########.fr       */
>>>>>>> ...
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

<<<<<<< HEAD
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
		return ((int)write(2, "syntax error! `unmatched quotes'\n", 34));
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
	head = NULL;
	while (arr[i])
	{
		if (is_whitespace(arr[i]))
			whitespace_handler(&head, arr, &i);
		else if (is_separator(arr[i]))
			separator_handler(&head, arr, &i);
		else if (is_quotes(arr[i]))
		{
			if (quotes_handler(&head, arr, &i))
				return (freeptr(&arr), lstclear_tokens(&head), NULL);
		}
		else
			char_handler(&head, arr, &i);
	}
	return (free(arr), head);
}
=======
t_token		*tokenizer(char *line)
{


	

}
>>>>>>> ...
