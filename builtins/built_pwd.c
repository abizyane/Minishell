/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:27:10 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/14 16:01:23 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_cmdline *cmd, t_env *env)
{
	char	*path;

	(void)cmd;
	path = getcwd(NULL, 1024);
	if (path)
	{
		ft_putendl_fd(path, STDOUT_FILENO);
		free(path);
	}
	else if (find_var(env, "PWD"))
		ft_putendl_fd(find_var(env, "PWD"), STDOUT_FILENO);
	else if (find_var(env, "OLDPWD"))
		ft_putendl_fd(find_var(env, "OLDPWD"), STDOUT_FILENO);
	else
	{
		perror("pwd:");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
