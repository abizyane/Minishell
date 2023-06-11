/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:13:44 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/09 14:10:42 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
=======
/*   By: abizyane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:13:44 by abizyane          #+#    #+#             */
/*   Updated: 2022/10/26 16:47:27 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
>>>>>>> ...

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	j;
	size_t	l;

	j = 0;
	l = ft_strlen(src);
	if (dstsize == 0)
		return (l);
	while (src[j] && j < (dstsize - 1))
	{
		dst[j] = src[j];
		j++;
	}
	dst[j] = '\0';
	return (l);
}
