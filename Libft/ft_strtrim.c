/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:19:02 by abizyane          #+#    #+#             */
/*   Updated: 2023/06/20 20:57:03 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

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
