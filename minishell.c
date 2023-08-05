/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:00:28 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/05 12:57:45 by ahamrad          ###   ########.fr       */
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

int main(int ac, char *av[], char **env)
{
	char		*line;
	t_cmdline	*cmd_line;

	(void)ac;
	(void)av;
    signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline(GRN" -> "CYN"Minishell "RST);
        if (!line)
            return  0;
		add_history(line);
		if (line[0] != '\0' && !check_spaces(line))
		{
			cmd_line = parse_line(line);
			if (!cmd_line)
				exit(1);
			execution(cmd_line, env);
		}
	}
}
