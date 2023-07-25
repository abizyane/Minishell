/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:41:38 by abizyane          #+#    #+#             */
/*   Updated: 2023/06/20 20:56:27 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

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
