/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 02:47:23 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/09 21:17:40 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_arr_dup(char **arr)
{
	char	**new;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	new = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		if (!new[i])
		{
			free_arr(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
