/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 02:55:41 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/14 19:55:31 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (cmd->redir)
		redirections(cmd);
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

	if (cmd->nxt && pipe(fd) == -1)
		perror("pipe");
	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		if (cmd->redir)
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

int	handle_builtin_redir(t_cmdline *cmd)
{
	t_redir	*tmp;

	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->type == redOut || tmp->type == redApp)
		{
			if (handle_outfile(tmp) == 0)
				return (0);
		}
		else if (tmp->type == redIn)
		{
			if (handle_infile(tmp) == 0)
				return (0);
		}
		else if (tmp->type == Heredoc)
		{
			dup2(tmp->fd, STDIN_FILENO);
			close(tmp->fd);
		}
		tmp = tmp->nxt;
	}
	return (1);
}

void	execution(t_cmdline *cmd, t_env *env, int input_save, int output_save)
{
	int		status;
	int		pid;
	char	**envp;

	envp = lst_to_arr(env);
	g_data.rl = 1;
	if (execute_builtin_redir(cmd, env) == 1)
		return (free_arr(envp));
	if (execute_builtin2(cmd, env) == 1)
		return (free_arr(envp));
	input_save = dup(STDIN_FILENO);
	output_save = dup(STDOUT_FILENO);
	while (cmd)
	{
		pid = execute_command(cmd, envp, env);
		cmd = cmd->nxt;
	}
	waitpid(pid, &status, 0);
	while (waitpid(-1, NULL, 0) != -1)
		;
	get_exit_status(status);
	close_dup(input_save, output_save);
	g_data.rl = 0;
	free_arr(envp);
}
