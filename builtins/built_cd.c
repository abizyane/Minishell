/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:18:35 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/10 12:47:11 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_error(char *path, int i)
{
	if (i == 1)
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory.\n", 2);
	if (i == 2 && path)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

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
	return (freeptr(&s1) , dst);
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

void	update_pwd(t_env *env, char *nwd)
{
	char	*pwd[2];

	pwd[1] = NULL;
	if (!find_env(env, "PWD"))
	{
		pwd[0] = ft_strdup("PWD");
		env_add_back(&env, pwd);
	}
	if (!find_env(env, "OLDPWD"))
	{
		pwd[0] = ft_strdup("OLDPWD");
		env_add_back(&env, pwd);
	}
	if (find_env(env, "PWD")->content)
	{
		free(find_env(env, "OLDPWD")->content);
		find_env(env, "OLDPWD")->content = ft_strdup(find_env(env, "PWD")->content);
		free(find_env(env, "PWD")->content);
	}
	find_env(env, "PWD")->content = getcwd(NULL, 0);
	if (!find_env(env, "PWD")->content)
	{
		find_env(env, "PWD")->content = ft_strjoin(find_env(env,"OLDPWD")->content, "/");
		find_env(env, "PWD")->content = free_strjoin(find_env(env, "PWD")->content, nwd);
	}
		
}


int	cd(t_cmdline *cmd, t_env *env)
{
	char	*tmp;

	if (!cmd->args[1] || cmd->args[1][0] == '~')
	{
		tmp = get_home(env);
		if (chdir(tmp) == -1 && !cmd->args[1])
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), EXIT_FAILURE);
	}
	else if (!ft_strcmp(cmd->args[1], ".") || !ft_strcmp(cmd->args[1], ".."))
	{
		tmp = getcwd(NULL, 0);
		if (chdir(cmd->args[1]) == -1 || !tmp)
			cd_error(cmd->args[1], 1);
		free(tmp);
	}
	else if (chdir(cmd->args[1]) == -1)
		return(cd_error(cmd->args[1], 2), EXIT_FAILURE);
	return (update_pwd(env, cmd->args[1]), EXIT_SUCCESS);
}