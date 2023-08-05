/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:00:47 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/05 05:18:21 by ahamrad          ###   ########.fr       */
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

void	read_heredoc(t_redir *redir, int *fd)
{
	char *line;
	char *dlm;

	dlm = redir->filename;
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("heredoc $> ");
		if (!line || !ft_strcmp(line, dlm))
			break;
		if (redir->heredoc_flag == 1)
        	line = expand_vars(line);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		freeptr(&line);
	}
	freeptr(&line);
	close(fd[1]);
	exit(0);
}

//TODO: if there is quotes in the delimiter the input stays the same

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
					read_heredoc(redir, fd);
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
