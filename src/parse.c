/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:00:35 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/14 15:34:17 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		token = token->nxt;
	}
	return (cmd);
}

void	get_token_type(t_token **head)
{
	t_token	*token;

	token = (*head);
	while (token)
	{
		if (token->type == Word && (!token->prv || (token->prv
					&& token->prv->type == Pipe)))
			token->type = Cmd;
		else if (token->type == Word && (token->prv->type == Cmd
				|| token->prv->type == Arg || token->prv->type == Fname))
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

	cmd = NULL;
	token_head = tokenizer(line);
	if (!token_head)
	{
		g_data.exit_status = 258;
		return (lstclear_tokens(&token_head), NULL);
	}
	if (check_tokens(&token_head) != 0)
	{
		g_data.exit_status = 258;
		return (lstclear_tokens(&token_head), NULL);
	}
	expand_env_var(&token_head, env);
	remove_quotes(&token_head);
	get_token_type(&token_head);
	cmd = fill_outstruct(&token_head);
	open_heredoc(&cmd, env);
	return (lstclear_tokens(&token_head), cmd);
}
