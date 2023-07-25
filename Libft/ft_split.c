/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:34:25 by abizyane          #+#    #+#             */
/*   Updated: 2023/06/20 20:56:40 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static size_t	countst(char const *str, char c)
{
	size_t	l;
	size_t	k;

	l = 0;
	k = 0;
	while (str[k])
	{
		while (str[k] == c)
			k++;
		if (str[k] != c && str[k])
		{
			l++;
			while (str[k] != c && str[k])
				k++;
		}
	}
	return (l);
}

static void	free_tab(char **s, int l)
{
	int	i;

	i = 0;
	while (i < l)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static int	next_spl(const char *s, char **str, char c, int *x)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	str[(*x)] = ft_substr(s, 0, i);
	if (str[(*x)] == NULL)
	{
		free_tab(str, (*x));
		return (-1);
	}
	(*x)++;
	return (i);
}

static char	**splitx(char const *s, char c)
{
	int		i;
	int		j;
	int		x;
	char	**str;

	i = 0;
	x = countst(s, c);
	str = ft_calloc(x + 1, sizeof(char *));
	if (!str)
		return (NULL);
	x = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			j = next_spl(&s[i], str, c, &x);
			if (j == -1)
				return (NULL);
			i += j;
		}
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	if (!s)
		return (NULL);
	return (splitx(s, c));
}
