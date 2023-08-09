/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:00:47 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/09 17:56:46 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*freeptr(char **s)
{
	if (*s)
	{
		free (*s);
		*s = NULL;
	}
	return (*s);
}

void	handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	ioctl(0, TIOCSTI, "\4");
}

int	read_heredoc(t_redir *redir, t_env *env)
{
	char	*line;
	char	*dlm;
	int		fd[2];

	(void)env;
	dlm = redir->filename;
	if (pipe(fd) == -1)
		return (perror("minishell"), -1);
	while (1)
	{
		signal(SIGINT, handler);
		line = readline("heredoc $> ");
		if (!line || !ft_strcmp(line, dlm))
			break ;
		if (redir->heredoc_flag == 0)
			line = expand_vars(line, env);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		freeptr(&line);
	}
	freeptr(&line);
	close(fd[1]);
	return (fd[0]);
}

void	open_heredoc(t_cmdline **head, t_env *env)
{
	t_cmdline	*cmd;
	t_redir		*redir;

	cmd = *head;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == Heredoc)
			{
				redir->fd = read_heredoc(redir, env);
				if (redir->fd == -1)
					return ;
			}
			redir = redir->nxt;
		}
		cmd = cmd->nxt;
	}
}
