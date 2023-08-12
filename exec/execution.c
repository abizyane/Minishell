/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 02:55:41 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/12 03:01:27 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (ft_strchr(cmd, '/') && access(cmd, F_OK) == -1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": command not found\n", 2);
}

void	local_binary(t_cmdline *cmd, char **envp)
{
	if (!cmd->args || !cmd->args[0])
		exit(EXIT_SUCCESS);
	if (access(cmd->args[0], F_OK | X_OK) == 0)
	{
		if (execve(cmd->args[0], cmd->args, envp) == -1)
		{
			not_found(cmd->args[0]);
			exit(126);
		}
	}
}

void	child_execution(t_cmdline *cmd, char **envp, int *fd, t_env *env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmd->args || !cmd->args[0])
		exit(EXIT_SUCCESS);
	if (cmd->nxt && redirection_check_out(cmd->redir) == 0)
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
		cmd->path = get_cmd_path(cmd, env);
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
	if (cmd->nxt && redirection_check_in(cmd->redir) == 0)
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
	g_rl = 1;
	input_save = dup(STDIN_FILENO);
	if (execute_builtin2(cmd, env) == 1)
	{
		free_arr(envp);
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
	get_exit_status(status);
	dup2(input_save, STDIN_FILENO);
	g_rl = 0;
	free_arr(envp);
}
