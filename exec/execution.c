/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 02:55:41 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/06 19:27:47 by abizyane         ###   ########.fr       */
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
	if (cmd->args[0][0] == '/')
		return (get_cmd(cmd));
	if (cmd->args[0][0] == '.')
		return (cmd->args[0]);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd->args[0]);
		if (access(path, F_OK) == 0)
			break ;
		i++;
	}
	if (!paths[i])
		return (NULL);
	return (path);
}

void	not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
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

void	execute_builtin(t_cmdline *cmd, char **envp, t_env *envi)
{
	(void)envp;
	if (!ft_strcmp(cmd->args[0], "echo"))
		exit_status = echo(cmd);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		exit_status = pwd(cmd);
	if (!ft_strcmp(cmd->args[0], "env"))
		exit_status = env(cmd, envi);
	// if (!ft_strcmp(cmd->args[0], "cd"))
	// 	exit_status = cd(cmd, env);
	if (!ft_strcmp(cmd->args[0], "exit"))
		exit_status = ft_exit(cmd);
}

void	local_binary(t_cmdline *cmd, char **envp)
{
	if (!cmd->args || !cmd->args[0])
		exit(EXIT_SUCCESS);
	if (access(cmd->args[0], X_OK) == 0)
	{
		if (execve(cmd->args[0], cmd->args, envp) == -1)
		{
			not_found(cmd->args[0]);
			exit(127);
		}
	}
}

void	child_execution(t_cmdline *cmd, char **envp, int *fd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmd->args || !cmd->args[0])
		exit(EXIT_SUCCESS);
	if (cmd->redir)
		redirections(cmd);
	if (cmd->nxt)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
	local_binary(cmd, envp);
	cmd->path = get_cmd_path(cmd, envp);
	if (execve(cmd->path, cmd->args, envp) == -1)
	{
		not_found(cmd->args[0]);
		exit(127);
	}
}

int	execute_command(t_cmdline *cmd, char **envp)
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
		child_execution(cmd, envp, fd);
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

void	execution(t_cmdline *cmd, char **envp, t_env *env)
{
	int		input_save;
	int		status;
	int		pid;

	rl = 1;
	input_save = dup(STDIN_FILENO);
	(void)env;
	// if (cmd && !cmd->nxt && ft_check_builtin(cmd->args[0]) == 1)
	// {
	// 	execute_builtin(cmd, envp, env);
	// 	return ;
	// }
	while (cmd)
	{
		pid = execute_command(cmd, envp);
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
}
