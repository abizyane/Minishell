/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 02:55:41 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/01 03:52:22 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    not_found(char *cmd)
{
    ft_putstr_fd("minishell: ", 2);
	if (cmd)
    	ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": command not found\n", 2);
}

char	*get_cmd(t_cmdline *cmd)
{
    char	**path;
    char	*arr;
    int i;

    i = 0;
    arr = cmd->args[0];
    path = ft_split(cmd->args[0], '/');
    if (!path)
        return (NULL);
    while (path[i])
        i++;
    cmd->args[0] = path[--i];
    return(free_arr(path), arr);
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
    if (cmd->args[0][0] == '/')
        return (get_cmd(cmd));
    if (cmd->args[0][0] == '.')
        return cmd->args[0];
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

void    close_fds(int fd[2])
{
    close(fd[0]);
    close(fd[1]);
}

int		handle_multi_cmds(t_cmdline *cmd, char **envp)
{
    int pid;
    int status;
    
    while (cmd)
    {
        if (cmd->nxt)
            pipe(cmd->pipe);
        pid = fork();
        if (pid == 0)
        {
            if (cmd->nxt)
                dup2(cmd->pipe[1], STDOUT_FILENO);
            redirections(cmd);
            close_fds(cmd->pipe);
            cmd->path = get_cmd_path(cmd, envp);
            // if (!cmd->path)
            //     return (127);
            if (execve(cmd->path, cmd->args, envp) == -1)
            {
                not_found(cmd->args[0]);
                if (errno == 14)
                    exit(127);
            }
        }
        else if (cmd->nxt)
            dup2(cmd->pipe[0], STDIN_FILENO);
        close_fds(cmd->pipe);
        cmd = cmd->nxt;
    }
    while (wait(&status) != -1)
        ;
    // if (WIFEXITED(status))
    //     return (WEXITSTATUS(status));
    // if (WIFSIGNALED(status))
    //     return (WTERMSIG(status));
    return 0;
}

//char	*str_join(char *s1, char *s2)
//{
//    size_t	i;
//    size_t	j;
//    size_t	l;
//    char	*dst;
//
//    i = -1;
//    j = -1;
//    if (!s1)
//        return (s2);
//    l = ft_strlen(s1) + ft_strlen(s2);
//    dst = ft_calloc((l + 2), sizeof(char));
//    if (!dst)
//        return (NULL);
//    while (s1[++i])
//        dst[i] = s1[i];
//    dst[i++] = '/';
//    while (s2[++j])
//        dst[i + j] = s2[j];
//    return (freeptr(&s2) ,dst);
//}

// int    execute_single_cmd(t_cmdline *cmd, char **envp)
// {
// 	pid_t   pid;
// 	int     status;

// 	if (cmd->args[0][0] != '/')
// 		cmd->path = get_cmd_path(cmd, envp);
// 	else
// 		cmd->path = cmd->args[0];
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (execve(cmd->path, cmd->args, envp) == -1)
// 		{
// 			printf("%s\n", strerror(errno));
// 			perror("execve");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else if (pid < 0)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{
// 		wait(&status);
// 		if (WIFEXITED(status))
// 			return (WEXITSTATUS(status));
// 	}
// 	return (0);
// }

// int 	execute_two_commands(t_cmdline *cmd, char **envp)
// {
// 	int		fd[2];
// 	int		pid1, pid2;

// 	if (pipe(fd) == -1)
// 		perror("pipe");
// 	pid1 = fork();
// 	if (pid1 < 0)
// 		perror("fork");
// 	if (pid1 == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[1]);
// 		cmd->path = get_cmd_path(cmd, envp);
// 		if (execve(cmd->path, cmd->args, envp) == -1)
// 		{
// 			printf("%s\n", strerror(errno));
// 			perror("execve");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else
// 		wait(NULL);
// 	pid2 = fork();
// 	if (pid2 < 0)
// 		perror("fork");
// 	if (pid2 == 0)
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		cmd->nxt->path = get_cmd_path(cmd->nxt, envp);
// 		if (execve(cmd->nxt->path, cmd->nxt->args, envp) == -1)
// 		{
// 			printf("%s\n", strerror(errno));
// 			perror("execve");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else
// 	{
// 		close(fd[0]);
// 		close(fd[1]);
// 		wait(NULL);
// 	}
// 	return 0;
// }

//TODO:cat minishell.c > > a