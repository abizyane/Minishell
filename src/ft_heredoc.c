/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:00:47 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/10 15:04:24 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    *freeptr(char **s)
{
    if (*s)
    {
        free (*s);
        *s = NULL;
    }
    return (*s);
}

void    handler(int sig)
{
    (void)sig;
    rl_on_new_line();
    rl_replace_line("", 0);
    g_rl = 1;
    ioctl(0, TIOCSTI, "\4");
}

int    read_heredoc(t_redir *redir, t_env *env)
{
    char    *line;
    char    *dlm;
    int        fd[2];

    (void)env;
    dlm = redir->filename;
    if (pipe(fd) == -1)
        return (perror("minishell"), -1);
    signal(SIGINT, handler);
    while (1)
    {
        line = readline("> ");
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

void	close_heredoc_fds(t_cmdline *cmd)
{
	t_cmdline	*p;
	t_redir		*q;

	p = cmd;
	while (p)
	{
		q = p->redir;
		while (q)
		{
			if (q->type == Heredoc)
				close(q->fd);
			q = q->nxt;
		}
		p = p->nxt;
	}
}

void    open_heredoc(t_cmdline **head, t_env *env)
{
    t_cmdline    *cmd;
    t_redir        *redir;

    cmd = *head;
    while (cmd)
    {
        redir = cmd->redir;
        while (redir)
        {
            if (redir->type == Heredoc && g_rl == 0)
            {
                redir->fd = read_heredoc(redir, env);
                if (redir->fd == -1)
                    return ;
            }
            redir = redir->nxt;
        }
        cmd = cmd->nxt;
    }
    g_rl = 0;
}
