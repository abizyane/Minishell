/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 21:34:02 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/09 14:11:50 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
=======
/*   By: abizyane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 21:34:02 by abizyane          #+#    #+#             */
/*   Updated: 2022/10/21 21:37:36 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
>>>>>>> ...

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
<<<<<<< HEAD
	if (n == 0 || (!s1 && !s2))
		return (0);
	if (!s1 || !s2)
		return (1);
=======
	if (n == 0)
		return (0);
>>>>>>> ...
	while ((s1[i] && s2[i]) && (i < n - 1) && s1[i] == s2[i])
		i++;
	if (((unsigned char)s1[i] - (unsigned char)s2[i]) > 0)
		return (1);
	if (((unsigned char)s1[i] - (unsigned char)s2[i]) < 0)
		return (-1);
	return (0);
}
<<<<<<< HEAD

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (s1 && !s2)
		return (1);
	if (!s1 && s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
=======
>>>>>>> ...
