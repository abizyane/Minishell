/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:00:28 by abizyane          #+#    #+#             */
/*   Updated: 2024/07/01 17:43:48 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global g_data;

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

void	close_all_redirs(t_cmdline *cmd)
{
	t_redir	*tmp;

	if (!cmd)
		return ;
	tmp = cmd->redir;
	while (tmp)
	{
		close(tmp->fd);
		tmp = tmp->nxt;
	}
	close_all_redirs(cmd->nxt);
}

void	ft_minishell(char **line, t_env **env_head, t_cmdline **cmd_line)
{
	while (1)
	{
		sig_handler();
		*line = readline(GRN" -> "CYN"Minishell "RST);
		if (!(*line))
			return (free_env(env_head), ft_putstr_fd("exit\n", 1));
		if ((*line)[0] != '\0' && !check_spaces(*line))
		{
			add_history(*line);
			*cmd_line = parse_line(*line, *env_head);
			if (!(*cmd_line) || g_data.rl == 2)
			{
				if (g_data.rl == 2)
					g_data.rl = 0;
				freeptr(line);
				continue ;
			}
			execution(*cmd_line, *env_head, 0, 0);
			free_cmd(cmd_line);
		}
		freeptr(line);
	}
}

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
	g_data.rl = 0;
	ft_minishell(&line, &env_head, &cmd_line);
	free_env(&env_head);
	close_all_redirs(cmd_line);
}
