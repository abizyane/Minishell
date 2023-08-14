/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:45:57 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/14 17:37:52 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_paths_from_env(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_cmdline *cmd, t_env *envp)
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	path = NULL;
	if (!cmd->args || !cmd->args[0])
		return (NULL);
	paths = ft_split(find_var(envp, "PATH"), ':');
	if (!paths)
		return (NULL);
	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = free_strjoin(path, cmd->args[0]);
		if (access(path, F_OK | X_OK) == 0)
			break ;
		i++;
		free(path);
	}
	free_arr(paths);
	return (path);
}

void	close_dup(int in, int out)
{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		close(in);
		close(out);
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
		g_data.exit_status = echo(cmd);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		g_data.exit_status = pwd(cmd, envi);
	if (!ft_strcmp(cmd->args[0], "env"))
		g_data.exit_status = ft_env(cmd, envi);
	if (!ft_strcmp(cmd->args[0], "cd"))
		g_data.exit_status = cd(cmd, envi);
	if (!ft_strcmp(cmd->args[0], "exit"))
		g_data.exit_status = ft_exit(cmd, exit_f);
	if (!ft_strcmp(cmd->args[0], "export"))
		g_data.exit_status = ft_export(cmd, &envi);
	if (!ft_strcmp(cmd->args[0], "unset"))
		g_data.exit_status = unset(cmd, &envi);
	// if (cmd->redir)
		close_dup(input_save, output_save);
}

void	exec_builtin_redir(t_cmdline *cmd, t_env *envi, int exit_f)
{
	int		input_save;
	int		output_save;
	
	input_save = dup(STDIN_FILENO);
	output_save = dup(STDOUT_FILENO);
	if (cmd->redir)
		if (handle_builtin_redir(cmd) == 0)
			return ;
	if (!ft_strcmp(cmd->args[0], "echo"))
		g_data.exit_status = echo(cmd);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		g_data.exit_status = pwd(cmd, envi);
	if (!ft_strcmp(cmd->args[0], "env"))
		g_data.exit_status = ft_env(cmd, envi);
	if (!ft_strcmp(cmd->args[0], "cd"))
		g_data.exit_status = cd(cmd, envi);
	if (!ft_strcmp(cmd->args[0], "exit"))
		g_data.exit_status = ft_exit(cmd, exit_f);
	if (!ft_strcmp(cmd->args[0], "export"))
		g_data.exit_status = ft_export(cmd, &envi);
	if (!ft_strcmp(cmd->args[0], "unset"))
		g_data.exit_status = unset(cmd, &envi);
	if (cmd->redir)
		close_dup(input_save, output_save);
}
