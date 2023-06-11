/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:41:38 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/09 14:08:48 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
=======
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:41:38 by abizyane          #+#    #+#             */
/*   Updated: 2022/11/21 14:15:50 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
>>>>>>> ...

void	*ft_memmove(void *dst, const void *src, size_t l)
{
	char		*d;
	const char	*s;
	size_t		i;

	d = (char *)dst;
	s = (const char *)src;
	i = 0;
	if (l == 0)
		return (dst);
	if (src > dst)
		ft_memcpy(dst, src, l);
	if (dst > src)
	{
		i = (l - 1);
		while (i > 0)
		{
			d[i] = s[i];
			i--;
		}
		if (i == 0)
			d[i] = s[i];
	}
	return (dst);
}
