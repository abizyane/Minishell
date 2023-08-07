/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:00:28 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/07 21:14:35 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->nxt;
	}
	arr = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		arr[i] = ft_strjoin(env->key, "=");
		arr[i] = ft_strjoin(arr[i], env->content);
		i++;
		env = env->nxt;
	}
	arr[i] = NULL;
	return (arr);
}

char	**empty_env(void)
{
	char	**env;

	env = ft_calloc(5, sizeof(char *));
	env[0] = ft_strjoin("PATH=", ft_strdup(PATH));
	env[1] = ft_strjoin("PWD=", getcwd(NULL, 1024));
	env[2] = ft_strdup("SHLVL=1");
	env[3] = ft_strdup("_=/usr/bin/env");
	env[4] = NULL;
	return (env);
}

void update_shlvl(t_env **env)
{
	t_env	*tmp;
	int		shlvl;
	
	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "SHLVL") == 0)
		{
			shlvl = ft_atoi(tmp->content) + 1;
			if (shlvl < 0 || shlvl >= 1000)
				shlvl = 1;
			free(tmp->content);
			tmp->content = ft_itoa(shlvl);
		} 
		tmp = tmp->nxt;		
	}
}

int main(int ac, char *av[], char **env)
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
		line = readline(GRN" -> "CYN"Minishell "RST);
		if (!line)
			return 0;
		add_history(line);
		if (line[0] != '\0' && !check_spaces(line))
		{
			cmd_line = parse_line(line, env_head);
			if (!cmd_line)
				continue ;
			execution(cmd_line, env_head);
		}
	}
}
//TODO: $? expanding