/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:52:49 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/09 14:09:07 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t l)
{
	unsigned char	*str;
	size_t			i;

	str = s;
	i = 0;
	while (i < l)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
