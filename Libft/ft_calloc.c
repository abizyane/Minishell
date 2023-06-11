/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:55:23 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/10 07:56:39 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
=======
/*   By: abizyane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:55:23 by abizyane          #+#    #+#             */
/*   Updated: 2022/10/26 16:54:32 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
>>>>>>> ...

void	*ft_calloc(size_t count, size_t size)
{
	void	*x;

	x = malloc(size * count);
	if (!x)
<<<<<<< HEAD
		exit(1);
=======
		return (NULL);
>>>>>>> ...
	ft_bzero(x, count * size);
	return (x);
}
