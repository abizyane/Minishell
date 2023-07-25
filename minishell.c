/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:00:28 by abizyane          #+#    #+#             */
/*   Updated: 2023/06/20 20:58:48 by abizyane         ###   ########.fr       */
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
	exit(0);
}
//			while (cmd_line && cmd_line->args)
//			{
//				int k = 0;
//				int f = 0;
//				while (cmd_line->args && cmd_line->args[k])
//				{
//					printf("args[%d]  == %s\n", f, cmd_line->args[k]);
//					f++;
//					k++;
//				}
//				if (cmd_line->redir)
//					while (cmd_line->redir)
//					{
//						printf("first redir filename == %s\n", cmd_line->redir->filename);
//						cmd_line->redir = cmd_line->redir->nxt;
//					}
//				printf("next command\n");
//				cmd_line = cmd_line->nxt;
//			}
