/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 23:29:11 by ahamrad           #+#    #+#             */
/*   Updated: 2023/07/26 19:59:27 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    redirections(t_cmdline *cmd)
{
    t_redir *tmp;

    tmp = cmd->redir;
    while (tmp)
    {
        if (tmp->type == redOut)
        {
            tmp->fd = open(tmp->filename, O_RDWR | O_CREAT | O_TRUNC, 0666);
            dup2(tmp->fd, STDOUT_FILENO);
            close(tmp->fd);
        }
        else if (tmp->type == redApp)
        {
            tmp->fd = open(tmp->filename, O_RDWR| O_CREAT | O_APPEND, 0666);
            dup2(tmp->fd, STDOUT_FILENO);
            close(tmp->fd);
        }
        else if (tmp->type == redIn)
        {
            tmp->fd = open(tmp->filename, O_RDONLY);
            if (tmp->fd != -1)
            {
                dup2(tmp->fd, STDIN_FILENO);
                close(tmp->fd);
            }
            else 
                ft_putendl_fd("No such file or directory", STDERR_FILENO);
        }
         else if (tmp->type == Heredoc)
         {


            
         }
        tmp = tmp->nxt;
    }
    return (1);
}
