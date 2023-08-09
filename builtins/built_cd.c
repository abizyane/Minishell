/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:18:35 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/08 23:25:33 by abizyane         ###   ########.fr       */
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
   return (dst);
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

char	*update_pwd(t_env *env,char *nwd)
{
	char    *str;
	t_env	*tmp;

	if (!find_var(env, "PWD"))
	{
		char *arr[2] = {"PWD",
					getcwd(NULL, 1024)};
		env_add_back(&env, arr);
	}
	if (!find_var(env, "OLDPWD"))
	{
		char *arrr[2] = {"OLDPWD",
						find_var(env, "PWD")};
		env_add_back(&env, arrr);
	}
	str = getcwd(NULL, 0);
	tmp = find_env(env, "OLDPWD");
	// free(tmp->content);
	tmp->content = find_env(env, "PWD")->content;
	if (!str)
	{
		tmp = find_env(env, "PWD");
		tmp->content = str_join(tmp->content, nwd);
		return (nwd);
	}	
	find_env(env, "PWD")->content = str;
	return (nwd);
}

//TODO: cd - && cd ~

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
		if (ft_strcmp(cmd->args[1], ".") == 0 || ft_strcmp(cmd->args[1], "..") == 0)
		{
			char *tmp = getcwd(NULL, 0);
			if (chdir(update_pwd(env, cmd->args[1])) == -1 || !tmp)
				return(perror("cd: "), EXIT_FAILURE);
			
			return (EXIT_SUCCESS);
		}
		else
		{
			if (chdir(cmd->args[1]) == -1)
				return(perror("cd: "), EXIT_FAILURE);
			(void)update_pwd(env, cmd->args[1]);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
