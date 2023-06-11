/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:30:14 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/09 14:08:36 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
=======
/*   By: abizyane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:30:14 by abizyane          #+#    #+#             */
/*   Updated: 2022/10/24 11:24:32 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
>>>>>>> ...

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

	i = 0;
	d = dst;
	s = (char *) src;
	if (!d && !s)
		return (NULL);
	while (i < n)
	{
<<<<<<< HEAD
		d[i] = s[i];
		i++;
=======
			d[i] = s[i];
			i++;
>>>>>>> ...
	}
	return (dst);
}
