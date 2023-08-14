/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:00:32 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/10 13:34:35 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termcap.h>
# include <termios.h>
# include <unistd.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <paths.h>

// typedef struct s_global{
int			g_exit_status;
int			g_rl;
// };

typedef enum e_type
{
	Word = 1,
	Pipe,
	redIn,
	Heredoc,
	redOut,
	redApp, 
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
	int					fd;
	int					heredoc_flag;
	struct s_redir		*nxt;
}						t_redir;

typedef struct s_env
{
	char			*key;
	char			*content;
	int				export_f;
	int				p_flag;
	struct s_env	*nxt;
}				t_env;

typedef struct s_cmdline
{
	struct s_cmdline	*prv;
	char				*path;
	char				**args;
	int					in;
	int					out;
	struct s_redir		*redir;
	struct s_cmdline	*nxt;
}						t_cmdline;

t_token		*tokenizer(char *line);
t_cmdline	*parse_line(char *line, t_env *env);
t_token		*lstnew_token(char *line);
void		lstadd_token(t_token **head, char *line);
t_token		*last_token(t_token *head);
void		lstclear_tokens(t_token **head);
int			is_quotes(char c);
int			closed_quotes(char *str, int i);
int			is_whitespace(char c);
int			is_separator(char c);
int			check_tokens(t_token **head);
void		expand_env_var(t_token **head, t_env *env);
char		*replace_var(char *env_var, char *line, int start, t_env *env);
void		remove_quotes(t_token **token);
int			has_quates(char *str);
void		lstadd_command(t_cmdline **head, char *cmd, int size);
t_cmdline	*last_command(t_cmdline *head);
t_redir		*lstnew_redir(t_token *token);
void		lstadd_redir(t_redir **head, t_token *token);
t_redir		*last_redir(t_redir *head);
t_cmdline	*lstnew_command(char *cmd, int size);
void		*freeptr(char **s);
void		open_heredoc(t_cmdline **head, t_env *env);
char		*remove_ds(char *line, int start);
char		*expand_vars(char *line, t_env *env);
void		env_add_back(t_env **env_head, char	**env_var);
t_env		*find_env(t_env *head, char *key);
int			execute_single_cmd(t_cmdline *cmd, char **envp);
char		*get_cmd_path(t_cmdline *cmd, t_env *envp);
int			execute_cmds(t_cmdline *cmd, char **envp);
int			execute_two_commands(t_cmdline *cmd, char **envp);
int			handle_multi_cmds(t_cmdline *cmd, char **envp);
char		**ft_arr_dup(char **arr);
int			array_len(char **arr);
void		free_arr(char **arr);
int			redirections(t_cmdline *cmd);
void		sig_handler(void);
void		sig_int(int sig);
char		**lst_to_arr(t_env *env);
void		permission_denied(char *filename);
int			pwd(t_cmdline *cmd, t_env *env);
int			echo(t_cmdline *cmd);
void		print_args(t_cmdline *cmd, int flag, int i);
int			echo_option(char *arg);
char		*find_var(t_env *head, char *env_var);
t_env		*lst_env(char **env);
int			ft_exit(t_cmdline *cmd, int f);
int			ft_env(t_cmdline *cmd, t_env *env);
int			cd(t_cmdline *cmd, t_env *env);
int			ft_export(t_cmdline *cmd, t_env **env);
int			unset(t_cmdline *cmd, t_env **env);
void		local_binary(t_cmdline *cmd, char **envp);
void		child_execution(t_cmdline *cmd, char **envp, int *fd, t_env *env);
int			execute_command(t_cmdline *cmd, char **envp, t_env *env);
void		execution(t_cmdline *cmd, t_env *env);
int			ft_check_builtin(char *cmd);
void		execute_builtin(t_cmdline *cmd, t_env *envi, int exit_f);
void		free_env(t_env **env);
void		free_cmd(t_cmdline **cmd);
void		free_redir(t_redir **redir);
char		*free_strjoin(char *s1, char *s2);
int			execute_builtin2(t_cmdline *cmd, t_env *env);
void		get_exit_status(int status);
void		exec_builtin_redir(t_cmdline *cmd, t_env *envi, int exit_f);
int			handle_outfile(t_redir *tmp);
int			handle_infile(t_redir *tmp);
int			handle_builtin_redir(t_cmdline *cmd);

#endif
