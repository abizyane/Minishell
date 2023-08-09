/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:55:23 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/09 14:06:33 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*x;

	x = malloc(size * count);
	if (!x)
		return (NULL);
	ft_bzero(x, count * size);
	return (x);
}
