/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:00:32 by abizyane          #+#    #+#             */
/*   Updated: 2023/06/25 06:36:25 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>
# include <errno.h>

#define BLK "\e[1;90m"
#define RED "\e[1;91m"
#define GRN "\e[3;92m"
#define MAG "\e[1;95m"
#define CYN "\e[3;96m"
#define RST "\e[0m"

typedef enum e_type
{
	Word = 1,
	Pipe,    // |
	redIn,   // <
	Heredoc, // <<
	redOut,  // >
	redApp, // >>
	Space,
	Cmd,
	Arg,
	Fname,
}						e_type;

typedef struct s_token
{
	char				*line;
	e_type				type;
	int					s;
	struct s_token		*nxt;
	struct s_token		*prv;
}						t_token;

typedef struct s_redir
{
	e_type				type;
	char				*filename;
	int 				fd;
	struct s_redir		*nxt;
}						t_redir;

typedef struct s_cmdline
{
	struct s_cmdline	*prv;
	char				*path;
	char				**args;
	int					in;
	int					out;
	int					pipe[2];
	struct s_redir		*redir;
	struct s_cmdline	*nxt;
}						t_cmdline;

t_token					*tokenizer(char *line);
t_cmdline				*parse_line(char *line);
t_token					*lstnew_token(char *line);
void					lstadd_token(t_token **head, char *line);
t_token					*last_token(t_token *head);
void					lstclear_tokens(t_token **head);
int						is_quotes(char c);
int						closed_quotes(char *str, int i);
int						is_whitespace(char c);
int						is_separator(char c);
int						check_tokens(t_token **head);
void					expand_env_var(t_token **head);
void					remove_quotes(t_token **token);
int						has_quates(char *str);
void					lstadd_command(t_cmdline **head, char *cmd, int size);
t_cmdline				*last_command(t_cmdline *head);
t_redir					*lstnew_redir(t_token *token);
void					lstadd_redir(t_redir **head, t_token *token);
t_redir					*last_redir(t_redir *head);
t_cmdline				*lstnew_command(char *cmd, int size);
void					*freeptr(char **s);
void					open_heredoc(t_cmdline **head);



int    	execute_single_cmd(t_cmdline *cmd, char **envp);
char    *get_cmd_path(t_cmdline *cmd, char **envp);
int		execute_cmds(t_cmdline *cmd, char **envp);
int 	execute_two_commands(t_cmdline *cmd, char **envp);
int		handle_multi_cmds(t_cmdline *cmd, char **envp);
char    **ft_arr_dup(char **arr);
int     array_len(char **arr);
void    free_arr(char **arr);

#endif
