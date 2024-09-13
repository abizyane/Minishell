/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:05:44 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/14 17:20:17 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*str_join(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	l;
	char	*dst;

	i = -1;
	j = -1;
	if (!s1)
		return (s2);
	l = ft_strlen(s1) + ft_strlen(s2);
	dst = ft_calloc((l + 2), sizeof(char));
	if (!dst)
		return (NULL);
	while (s1[++i])
		dst[i] = s1[i];
	if (i > 0 && s1[i - 1] != '/')
		dst[i++] = '/';
	while (s2[++j])
		dst[i + j] = s2[j];
	return (freeptr(&s1), dst);
}

char	*get_home(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "HOME") == 0)
			return (tmp->content);
		tmp = tmp->nxt;
	}
	return (NULL);
}

t_env	*find_env(t_env *head, char *key)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->nxt;
	}
	return (NULL);
}

char	*free_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	l;
	char	*dst;

	i = -1;
	j = -1;
	if (!s1)
		return (s2);
	l = ft_strlen(s1) + ft_strlen(s2);
	dst = ft_calloc((l + 2), sizeof(char));
	if (!dst)
		return (NULL);
	while (s1[++i])
		dst[i] = s1[i];
	while (s2[++j])
		dst[i + j] = s2[j];
	return (freeptr(&s1), dst);
}

int	ft_check_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
