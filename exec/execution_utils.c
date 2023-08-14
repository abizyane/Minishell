/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 02:47:23 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/14 16:04:54 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

char	**ft_arr_dup(char **arr)
{
	char	**new;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	new = ft_calloc(sizeof(char *), (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		if (!new[i])
		{
			free_arr(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	not_found(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (ft_strchr(cmd, '/'))
	{
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
		ft_putstr_fd(": command not found\n", 2);
}

void	local_binary(t_cmdline *cmd, char **envp)
{
	struct stat	s;

	stat(cmd->args[0], &s);
	if (!cmd->args || !cmd->args[0])
		exit(EXIT_SUCCESS);
	if (access(cmd->args[0], X_OK | F_OK) == 0)
	{
		if (execve(cmd->args[0], cmd->args, envp) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->args[0], 2);
			if (S_ISDIR(s.st_mode))
				ft_putstr_fd(": is a directory\n", 2);
			else
				ft_putstr_fd(": Permission denied\n", 2);
			exit(126);
		}
	}
}
