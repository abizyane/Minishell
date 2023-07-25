/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:29:26 by abizyane          #+#    #+#             */
/*   Updated: 2023/06/20 20:57:01 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	l;
	char	*str;

	l = 0;
	i = start;
	if (!len || (start >= ft_strlen(s)) || !s)
		return (ft_strdup(""));
	if (ft_strlen(s) < len)
		str = ft_calloc(ft_strlen(s) - start + 1, sizeof(char));
	else
		str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s[i] && l < len)
	{
		str[l] = s[i];
		i++;
		l++;
	}
	return (str);
}
