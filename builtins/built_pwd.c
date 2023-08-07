/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:27:10 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/07 17:37:29 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    pwd(t_cmdline *cmd,t_env *env)
{
	(void)cmd;
	(void)env;
	char	*path;
	
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