/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 13:52:49 by abizyane          #+#    #+#             */
/*   Updated: 2023/06/20 20:56:29 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

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
