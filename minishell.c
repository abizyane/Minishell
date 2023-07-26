/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:00:28 by abizyane          #+#    #+#             */
/*   Updated: 2023/07/25 23:18:03 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	minishell(t_cmdline		*cmd_line, char ***env)
{
	if (handle_multi_cmds(cmd_line, *env) < 0)
		return ;
//	(void)cmd_line;
//	(void)env;
}

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

int main(int ac, char *av[], char **env)
{
	char		*line;
	t_cmdline	*cmd_line;

    cmd_line = NULL;
	int save_stdin = dup(STDIN_FILENO);
	(void)ac;
	(void)av;
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		line = readline(GRN" -> "CYN"Minishell "RST);
        if (!line)
            return  0;
		add_history(line);
		if (line[0] != '\0' && !check_spaces(line))
		{
			cmd_line = parse_line(line);
			minishell(cmd_line, &env);
		}
		dup2(save_stdin, STDIN_FILENO);
	}
}
