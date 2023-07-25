/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eymn <eymn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 02:55:41 by ahamrad           #+#    #+#             */
/*   Updated: 2023/07/24 01:57:37 by eymn             ###   ########.fr       */
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
	return (freeptr(&s2) ,dst);
}

char    *get_cmd_path(t_cmdline *cmd, char **envp)
{
	char    *path;
	char    **paths;
	int     i;

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

int    execute_single_cmd(t_cmdline *cmd, char **envp)
{
	pid_t   pid;
	int     status;

	if (cmd->args[0][0] != '/')
		cmd->path = get_cmd_path(cmd, envp);
	else 
		cmd->path = cmd->args[0];
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd->path, cmd->args, envp) == -1)
		{
			printf("%s\n", strerror(errno));
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (0);
}

int 	execute_two_commands(t_cmdline *cmd, char **envp)
{
	int		fd[2];
	int		pid1, pid2;
	
	if (pipe(fd) == -1)
		perror("pipe");
	pid1 = fork();
	if (pid1 < 0)
		perror("fork");
	if (pid1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		cmd->path = get_cmd_path(cmd, envp);
		if (execve(cmd->path, cmd->args, envp) == -1)
		{
			printf("%s\n", strerror(errno));
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
	pid2 = fork();
	if (pid2 < 0)
		perror("fork");
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		cmd->nxt->path = get_cmd_path(cmd->nxt, envp);
		if (execve(cmd->nxt->path, cmd->nxt->args, envp) == -1)
		{
			printf("%s\n", strerror(errno));
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else 
	{
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
	}
	return 0;
}

int		handle_multi_cmds(t_cmdline *cmd, char **envp)
{
	int fd[2];
	int pid;
	
	while (cmd)
	{
		if (cmd->nxt)
			pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (cmd->nxt)
			{
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
			}
			cmd->path = get_cmd_path(cmd, envp);
			if (!cmd->path)
				return (-1);
			if (execve(cmd->path, cmd->args, envp) == -1)
			{
				printf("%s\n", strerror(errno));
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else if (cmd->nxt)
		{
				close(fd[1]);
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
		}
		cmd = cmd->nxt;
	}
	while (wait(NULL) != -1)
		;
	return 0;
}