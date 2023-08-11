/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 17:45:57 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/10 10:19:32 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*free_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	l;
	char	*dst;

	i = -1;
	j = -1;
	if (!s1)
		return (s2);
	l = ft_strlen(s1) + ft_strlen(s2);
	dst = ft_calloc((l + 2), sizeof(char));
	if (!dst)
		return (NULL);
	while (s1[++i])
		dst[i] = s1[i];
	while (s2[++j])
		dst[i + j] = s2[j];
	return (freeptr(&s1), dst);
}

char	*get_cmd_path(t_cmdline *cmd, t_env *envp)
{
	char	*path;
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	path = NULL;
	if (!cmd->args || !cmd->args[0])
		return (NULL);
	paths = ft_split(find_var(envp, "PATH"), ':');
	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = free_strjoin(path, cmd->args[0]);
		if (access(path, F_OK | X_OK) == 0)
			break ;
		i++;
	}
	if (!paths || !paths[i])
		return (NULL);
	free_arr(paths);
	return (path);
}

int	ft_check_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	execute_builtin(t_cmdline *cmd, t_env *envi, int exit_f)
{
	int		input_save;
	int		output_save;
	
	input_save = dup(STDIN_FILENO);
	output_save = dup(STDOUT_FILENO);
	if (cmd->redir)
		redirections(cmd);
	if (!ft_strcmp(cmd->args[0], "echo"))
		g_exit_status = echo(cmd);
	if (!ft_strcmp(cmd->args[0], "pwd"))
		g_exit_status = pwd(cmd, envi);
	if (!ft_strcmp(cmd->args[0], "env"))
		g_exit_status = env(cmd, envi);
	if (!ft_strcmp(cmd->args[0], "cd"))
		g_exit_status = cd(cmd, envi);
	if (!ft_strcmp(cmd->args[0], "exit"))
		g_exit_status = ft_exit(cmd, exit_f);
	if (!ft_strcmp(cmd->args[0], "export"))
		g_exit_status = ft_export(cmd, &envi);
	if (!ft_strcmp(cmd->args[0], "unset"))
		g_exit_status = unset(cmd, &envi);
	if (cmd->redir)
	{
		dup2(input_save, STDIN_FILENO);
		dup2(output_save, STDOUT_FILENO);
	}
}
