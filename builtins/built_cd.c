/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:18:35 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/07 17:36:06 by abizyane         ###   ########.fr       */
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
   dst[i++] = '/';
   while (s2[++j])
       dst[i + j] = s2[j];
   return (freeptr(&s1) ,dst);
}


char    *get_home(t_env *env)
{
	t_env   *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "HOME") == 0)
			return (tmp->content);
		tmp = tmp->nxt;
	}
	return (NULL);
}

int     cd(t_cmdline *cmd, t_env *env)
{
	char    *home;

	if (!cmd->args[1])
	{
		home = get_home(env);
		if (chdir(home) == -1)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	}
	else
	{
		while (chdir(cmd->args[1]) == -1)
			cmd->args[1] = str_join(cmd->args[1], "../");
	}
	return (EXIT_FAILURE);
}
