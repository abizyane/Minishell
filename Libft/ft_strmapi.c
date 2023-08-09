/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:39:08 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/09 14:11:06 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*x;

	if (!s || !f)
		return (NULL);
	i = ft_strlen(s);
	x = ft_calloc((i + 1), sizeof(char));
	if (!x)
		return (NULL);
	i = 0;
	while (s[i])
	{
		x[i] = f(i, s[i]);
		i++;
	}
	return (x);
}
