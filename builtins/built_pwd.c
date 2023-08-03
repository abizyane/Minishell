/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:27:10 by ahamrad           #+#    #+#             */
/*   Updated: 2023/07/31 23:51:25 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    pwd(t_cmdline *cmd)
{
    (void)cmd;
    char    *path;
    
    path = getcwd(NULL, 1024);
    if (path)
    {
        ft_putendl_fd(path, STDOUT_FILENO);
        free(path);
        return (EXIT_SUCCESS);
    }
    else
        perror("pwd");
    return (EXIT_FAILURE);
}