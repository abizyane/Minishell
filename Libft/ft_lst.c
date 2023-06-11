/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 16:24:23 by abizyane          #+#    #+#             */
/*   Updated: 2023/06/10 21:01:44 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*lstnew_token(char *line)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	new->line = line;
	new->nxt = NULL;
	new->prv = NULL;
	return (new);
}

t_token	*last_token(t_token *head)
{
	t_token	*tmp;

	tmp = head;
	if (!head || !tmp->nxt)
		return (head);
	while (tmp->nxt)
		tmp = tmp->nxt;
	return (tmp);
}

void	lstadd_token(t_token **head, char *line)
{
	t_token	*new;
	t_token	*tmp;

	new = lstnew_phil(line);
	tmp = *head;
	if (!tmp)
		*head = new;
	else
	{
		while (tmp->nxt)
			tmp = tmp->nxt;
		tmp->nxt = new;
	}
}

