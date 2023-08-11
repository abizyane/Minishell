/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:00:35 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/11 20:08:29 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_token *head)
{
	int		i;

	i = 0;
	if (head && head->nxt && head->type == Pipe)
		head = head->nxt;
	while (head && head->type != Pipe)
	{
		if (head->type == Arg || head->type == Cmd)
			i++;
		head = head->nxt;
	}
	return (i + 1);
}

void	add_redir_fname(t_cmdline **head, t_token *token)
{
	t_cmdline	*tmp;
	t_redir		*r_tmp;

	tmp = last_command(*head);
	r_tmp = last_redir(tmp->redir);
	r_tmp->filename = ft_strdup(token->line);
	if (token->prv && token->prv->type == Heredoc && token->s == 1)
		r_tmp->heredoc_flag = 1;
}

void	add_args(t_cmdline **head, t_token *token)
{
	t_cmdline	*tmp;
	int			i;

	tmp = last_command(*head);
	i = 0;
	if (!tmp->args)
		tmp->args = ft_calloc(sizeof(char *), count_args(token));
	while (tmp->args && tmp->args[i] != 0)
		i++;
	tmp->args[i] = ft_strdup(token->line);
}


void	add_redir(t_cmdline **head, t_token *token)
{
	t_cmdline	*tmp;

	tmp = last_command(*head);
	lstadd_redir(&tmp->redir, token);
}

void	add_commands(t_cmdline **head, t_token *token)
{
	t_cmdline	*tmp;

	tmp = last_command(*head);
	if (!tmp->args)
		tmp->args = ft_calloc(sizeof(char *), count_args(token));
	tmp->args[0] = ft_strdup(token->line);
}

t_cmdline	*fill_outstruct(t_token **head)
{
	t_cmdline	*cmd;
	t_token		*token;

	token = *head;
	cmd = lstnew_command(NULL, count_args(token));
	while (token)
	{
		if (token->type == Cmd)
			add_commands(&cmd, token);
		else if (token->type == Pipe)
			lstadd_command(&cmd, NULL, count_args(token));
		else if (token->type == Fname)
			add_redir_fname(&cmd, token);
		else if (token->type == Arg)
			add_args(&cmd, token);
		else
			add_redir(&cmd, token);
		token = token->nxt ;
	}
	return (cmd);
}

void	get_token_type(t_token **head)
{
	t_token	*token;

	token = (*head);
	while (token)
	{
		if (token->type == Word && (!token->prv || (token->prv && token->prv->type == Pipe)))
			token->type = Cmd;
		else if (token->type == Word && (token->prv->type == Cmd || token->prv->type == Arg || token->prv->type == Fname))
			token->type = Arg;
		else if (token->type == Word)
			token->type = Fname;
		token = token->nxt;
	}
}

t_cmdline	*parse_line(char *line, t_env *env)
{
	t_token		*token_head;
	t_cmdline	*cmd;

	token_head = tokenizer(line);
	if (check_tokens(&token_head) != 0)
	{
		g_exit_status = 1;
		return (lstclear_tokens(&token_head), NULL);
	}
	expand_env_var(&token_head, env);
	remove_quotes(&token_head);
	get_token_type(&token_head);
	cmd = fill_outstruct(&token_head);
	open_heredoc(&cmd, env);
	return (lstclear_tokens(&token_head), cmd);
}
