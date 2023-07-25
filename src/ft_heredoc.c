/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:00:47 by abizyane          #+#    #+#             */
/*   Updated: 2023/07/15 19:00:47 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	*freeptr(char **s)
{
	if (*s)
	{
		free (*s);
		*s = NULL;
	}
	return (*s);
}

int	read_heredoc(char *dlm, int *fd)
{
	char *line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("heredoc $> ");
		if (!line || !ft_strcmp(line, dlm))
			break;
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		freeptr(&line);
	}
	freeptr(&line);
	close(fd[1]);
	exit(0);
}

void	open_heredoc(t_cmdline **head)
{
	t_cmdline	*cmd;
	t_redir 	*redir;
	int 		pid;
	int 		fd[2];
	int			status;

	cmd = *head;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == Heredoc)
			{
				if (pipe(fd) == -1)
					return (perror("heredoc pipe"));
				pid = fork();
				if (pid < 0)
					perror("heredoc fork");
				if (pid == 0)
					redir->fd = read_heredoc(redir->filename, fd);
				else
				{
					wait(&status);
					redir->fd = fd[0];
				}
			}
			redir = redir->nxt;
		}
		cmd = cmd->nxt;
	}
}