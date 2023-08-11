/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:00:28 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/11 20:17:59 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_spaces(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			j++;
		i++;
	}
	if (i == (int)ft_strlen(str) && j == 0)
		return (1);
	else
		return (0);
}

char	**lst_to_arr(t_env *env)
{
	int		i;
	char	**arr;
	t_env	*tmp;
	char	*tmp2;

	i = 0;
	tmp = env;
	while (tmp && ++i)
		tmp = tmp->nxt;
	arr = ft_calloc(sizeof(char *), i + 1);
	i = 0;
	while (env)
	{
		if (env->key)
		{
			tmp2 = ft_strjoin(env->key, "=");
			arr[i++] = ft_strjoin(tmp2, env->content);
			free(tmp2);
		}
		env = env->nxt;
	}
	return (arr);
}

char	**empty_env(void)
{
	char	**env;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	env = ft_calloc(4, sizeof(char *));
	env[0] = ft_strjoin("PWD=", cwd);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strdup("_=/usr/bin/env");
	env[3] = NULL;
	freeptr(&cwd);
	return (env);
}

void	update_shlvl(t_env **env)
{
	t_env	*tmp;
	int		shlvl;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "SHLVL") == 0)
		{
			if (!tmp->content)
				tmp->content = ft_strdup("0");
			shlvl = ft_atoi(tmp->content) + 1;
			if (shlvl < 0 || shlvl >= 1000)
				shlvl = 0;
			free(tmp->content);
			tmp->content = ft_itoa(shlvl);
		}
		tmp = tmp->nxt;
	}
}

/*
*	TODO: OLDPWD must be empty!! [in normal case and without environment]
*	TODO: PWD must be filled even if ENV is unsetted!!
*	TODO: Heredoc Ctrl+C not working || [Using boolean int to solve problem results] Ctrl+C ==> 'heredoc' ==> continue to exectue command [PROBLEM]
*	TODO: tests : Error Management [input: $USER | $HOME...] [Mine: minishell: /Users/abizyane: Permission denied || bash: bash: /Users/abizyane: is a directory]
*	TODO: More Tests Marouane's Norm [Expanding :: expand_env_var(t_token **head, t_env *env)]
*/

int	main(int ac, char *av[], char **env)
{
	char		*line;
	t_cmdline	*cmd_line;
	t_env		*env_head;

	(void)ac;
	(void)av;
	if (!env[0])
		env = empty_env();
	env_head = lst_env(env);
	update_shlvl(&env_head);
	while (1)
	{
		sig_handler();
		line = readline(" minishell-1.0$ ");
		if (!line)
			return (ft_putstr_fd("exit\n", STDOUT_FILENO), 0);
		if (line[0] != '\0' && !check_spaces(line))
		{
			add_history(line);
			cmd_line = parse_line(line, env_head);
			if (!cmd_line)
				continue ;
			execution(cmd_line, env_head);
			close_heredoc_fds(cmd_line);
			free_cmd(&cmd_line);
		}
	}
	free_env(&env_head);
}
