/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 02:48:44 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/09 14:09:52 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	l;
	size_t	i;
	char	*a;

	i = 0;
	l = ft_strlen(s1);
	a = ft_calloc(l + 1, sizeof(char));
	if (a == NULL)
		return (NULL);
	while (s1[i])
	{
		a[i] = s1[i];
		i++;
	}
	return (a);
}
