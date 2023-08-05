/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:29:11 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/05 15:09:44 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	no_file(char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	permission_denied(char *filename)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": Permission denied\n", 2);
}

int	handle_outfile(t_redir *tmp)
{
	if (tmp->type == redOut)
	{
		tmp->fd = open(tmp->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (access(tmp->filename, W_OK) == -1)
			return (permission_denied(tmp->filename), 0);
		if (tmp->fd < 0)
			return (0); 
		dup2(tmp->fd, STDOUT_FILENO);
		close(tmp->fd);
	}
	else if (tmp->type == redApp)
	{
		tmp->fd = open(tmp->filename, O_WRONLY| O_CREAT | O_APPEND, 0666);
		if (access(tmp->filename, W_OK) == -1)
			return (permission_denied(tmp->filename), 0);
		if (tmp->fd < 0)
			return (0);
		dup2(tmp->fd, STDOUT_FILENO);
		close(tmp->fd);
	}
	return (1);
}

int	handle_infile(t_redir *tmp)
{
	if (tmp->type == redIn)
	{
		tmp->fd = open(tmp->filename, O_RDONLY);
		if (access(tmp->filename, R_OK) == -1)
			return (permission_denied(tmp->filename), 0);
		if (tmp->fd < 0)
			return (no_file(tmp->filename), 0);
		dup2(tmp->fd, STDIN_FILENO);
		close(tmp->fd);
	}
	return (1);
}


int	redirections(t_cmdline *cmd)
{
	t_redir *tmp;

	tmp = cmd->redir;
	while (tmp)
	{
		if (tmp->type == redOut || tmp->type == redApp)
		{
			if (handle_outfile(tmp) == 0) 
				exit(EXIT_FAILURE);
		}
		else if (tmp->type == redIn)
		{
			if (handle_infile(tmp) == 0)
				exit(EXIT_FAILURE);
		}
		tmp = tmp->nxt;
	}
	return (1);
}
