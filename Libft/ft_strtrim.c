/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:19:02 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/09 14:12:07 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
=======
/*   By: abizyane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:19:02 by abizyane          #+#    #+#             */
/*   Updated: 2022/10/28 13:39:14 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
>>>>>>> ...

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	x;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	x = ft_strlen(s1) - 1;
	if ((int)x == -1)
		return (ft_substr(s1, 0, 0));
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	while (ft_strchr(set, s1[x]) && s1[x])
		x--;
	j = (x - i) + 1;
	return (ft_substr(s1, i, j));
}
