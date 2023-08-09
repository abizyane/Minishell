/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 02:55:41 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/09 10:07:24 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd(t_cmdline *cmd)
{
	char	**path;
	char	*arr;
	int		i;

	i = 0;
	arr = cmd->args[0];
	path = ft_split(cmd->args[0], '/');
	if (!path)
		return (NULL);
	while (path[i])
		i++;
	cmd->args[0] = path[--i];
	return (free_arr(path), arr);
}

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
		// else 
		// 	paths = ft_split(_PATH_STDPATH, ':');
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

void	not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (ft_strchr(cmd, '/'))
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
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
//TODO:signals fail when executing a subminishell
void	local_binary(t_cmdline *cmd, char **envp)
{
	if (!cmd->args || !cmd->args[0])
		exit(EXIT_SUCCESS);
	if (access(cmd->args[0], X_OK) == 0) // | X_OK
	{
		if (execve(cmd->args[0], cmd->args, envp) == -1)
		{
			printf("minishell: %s: Permission denied\n", cmd->args[0]);
			exit(127);
		}
	}
}

void	child_execution(t_cmdline *cmd, char **envp, int *fd, t_env *env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmd->args || !cmd->args[0])
		exit(EXIT_SUCCESS);
	if (cmd->nxt)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
	if (ft_check_builtin(cmd->args[0]) == 1)
	{
		execute_builtin(cmd, env, 0);
		exit(EXIT_SUCCESS);
	}
	if (ft_strncmp(cmd->args[0], ".", 1) && ft_strncmp(cmd->args[0], "/", 1))
		cmd->path = get_cmd_path(cmd, envp);
	local_binary(cmd, envp);
	if (execve(cmd->path, cmd->args, envp) == -1)
	{
		not_found(cmd->args[0]);
		exit(127);
	}
}

int	execute_command(t_cmdline *cmd, char **envp, t_env *env)
{
	int	pid;
	int	fd[2];

	if (cmd->nxt)
	{
		if (pipe(fd) == -1)
			perror("pipe");
	}
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		redirections(cmd);
		child_execution(cmd, envp, fd, env);
	}
	if (cmd->nxt)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	else
		close(STDIN_FILENO);
	return (pid);
}

void	execution(t_cmdline *cmd, t_env *env)
{
	int		input_save;
	int		status;
	int		pid;
	char	**envp;

	envp = lst_to_arr(env);
	rl = 1;
	input_save = dup(STDIN_FILENO);
	if (cmd->args && !cmd->nxt && ft_check_builtin(cmd->args[0]) == 1)
	{
		execute_builtin(cmd, env, 1);
		rl = 0;
		return ;
	}
	while (cmd)
	{
		pid = execute_command(cmd, envp, env);
		cmd = cmd->nxt;
	}
	waitpid(pid, &status, 0);
	while (waitpid(-1, NULL, 0) != -1)
		;
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		exit_status = 128 + WTERMSIG(status);
		if (exit_status == 131)
			ft_putstr_fd("Quit: 3\n", 1);
	}
	dup2(input_save, STDIN_FILENO);
	rl = 0;
	free_arr(envp);
}
