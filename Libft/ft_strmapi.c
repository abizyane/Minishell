/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:39:08 by abizyane          #+#    #+#             */
/*   Updated: 2023/06/20 20:56:52 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

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
