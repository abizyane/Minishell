/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:45:57 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/09 17:48:58 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd_path(t_cmdline *cmd, char **envp)
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	path = NULL;
	if (!cmd->args || !cmd->args[0])
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
		else 
			paths = ft_split(_PATH_STDPATH, ':');
		i++;
	}
	i = 0;
	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd->args[0]);
		if (access(path, F_OK | X_OK) == 0)
			break ;
		i++;
	}
	if (!paths || !paths[i])
		return (NULL);
	//TODO: a river of memory leaks in here and it needs to get the paths from the stdpaths if it didn't find it in the env_list
	return (path);
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

void	execute_builtin(t_cmdline *cmd, t_env *envi, int exit_f)
{
	int		input_save;
	int		output_save;
	
	input_save = dup(STDIN_FILENO);
	output_save = dup(STDOUT_FILENO);
	if (cmd->redir)
		redirections(cmd);
	if (!ft_strcmp(cmd->args[0], "echo"))
		exit_status = echo(cmd);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		exit_status = pwd(cmd, envi);
	if (!ft_strcmp(cmd->args[0], "env"))
		exit_status = env(cmd, envi);
	if (!ft_strcmp(cmd->args[0], "cd"))
		exit_status = cd(cmd, envi);
	if (!ft_strcmp(cmd->args[0], "exit"))
		exit_status = ft_exit(cmd, exit_f);
	if (!ft_strcmp(cmd->args[0], "export"))
		exit_status = ft_export(cmd, &envi);
	if (!ft_strcmp(cmd->args[0], "unset"))
		exit_status = unset(cmd, &envi);
	if (cmd->redir)
	{
		dup2(input_save, STDIN_FILENO);
		dup2(output_save, STDOUT_FILENO);
	}
}