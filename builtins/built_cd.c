/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:18:35 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/14 17:08:33 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_error(char *path, int i)
{
	if (i == 1)
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot \
		access parent directories: No such file or directory.\n",
			2);
	if (i == 2 && path)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

void	change_pwd(t_env *env, char *nwd)
{
	t_env	*tmp;

	tmp = NULL;
	if (find_env(env, "PWD")->content)
	{
		free(find_env(env, "OLDPWD")->content);
		tmp = find_env(env, "OLDPWD");
		tmp->content = ft_strdup(find_env(env, "PWD")->content);
		free(find_env(env, "PWD")->content);
	}
	tmp = find_env(env, "PWD");
	tmp->content = getcwd(NULL, 0);
	if (!find_env(env, "PWD")->content)
	{
		tmp = find_env(env, "PWD");
		tmp->content = ft_strjoin(find_env(env, "OLDPWD")->content, "/");
		tmp->content = free_strjoin(find_env(env, "PWD")->content, nwd);
	}
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
	change_pwd(env, nwd);
}

int	cd(t_cmdline *cmd, t_env *env)
{
	char	*tmp;

	if (!cmd->args[1] || cmd->args[1][0] == '~')
	{
		tmp = get_home(env);
		if (chdir(tmp) == -1 && !cmd->args[1])
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2),
				EXIT_FAILURE);
	}
	else if (!ft_strcmp(cmd->args[1], ".") || !ft_strcmp(cmd->args[1], ".."))
	{
		tmp = getcwd(NULL, 0);
		if (chdir(cmd->args[1]) == -1 || !tmp)
			cd_error(cmd->args[1], 1);
		free(tmp);
	}
	else if (chdir(cmd->args[1]) == -1)
		return (cd_error(cmd->args[1], 2), EXIT_FAILURE);
	return (update_pwd(env, cmd->args[1]), EXIT_SUCCESS);
}
