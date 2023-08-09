/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:00:35 by abizyane          #+#    #+#             */
/*   Updated: 2023/08/09 18:00:24 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_redir_fname(t_cmdline **head, t_token *token)
{
	t_cmdline	*tmp;
	t_redir		*r_tmp;
	char		*file_name;

	file_name = token->line;
	tmp = last_command(*head);
	r_tmp = last_redir(tmp->redir);
	r_tmp->filename = file_name;
	if (token->prv && token->prv->type == Heredoc && token->s == 1)
		r_tmp->heredoc_flag = 1;
}

void	add_args(t_cmdline **head, char *token)
{
	t_cmdline	*tmp;
	int			i;

	tmp = last_command(*head);
	i = 0;
	while (tmp->args && tmp->args[i] != 0)
		i++;
	tmp->args[i] = ft_strdup(token);
}

int	count_args(t_token **head)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = *head;
	while (tmp && tmp->type != Pipe)
	{
		if (tmp->type == Arg || tmp->type == Cmd)
			i++;
		tmp = tmp->nxt;
	}
	return (i + 1);
}

void	add_redir(t_cmdline **head, t_token *token)
{
	t_cmdline	*tmp;

	if (!(*head))
		(*head) = lstnew_command(NULL, count_args(&token));
	tmp = last_command(*head);
	lstadd_redir(&tmp->redir, token);
}

t_cmdline	*fill_outstruct(t_token **head)
{
	t_cmdline	*cmd;
	t_token		*token;

	token = *head;
	cmd = lstnew_command(NULL, 0);
	//TODO: double heredoc with the same delim not working , needs to add another cmd node
	while (token)
	{
		if (token->type == Cmd)
			lstadd_command(&cmd, token->line, count_args(&token));
		else if (token->type == Pipe && token->nxt->type != Cmd)
			lstadd_command(&cmd, NULL, count_args(head));
		else if (token->type == Fname)
			add_redir_fname(&cmd, token);
		else if (token->type == Arg)
		{
			if (!cmd->args)
				cmd->args = ft_calloc(sizeof(char *), count_args(head));
			add_args(&cmd, token->line);
		}
		else if (token->type != Pipe)
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
	t_cmdline	*cmd = NULL;

	token_head = tokenizer(line);
	if (check_tokens(&token_head) != 0)
		return (NULL);
	expand_env_var(&token_head, env);
	remove_quotes(&token_head);
	get_token_type(&token_head);
	cmd = fill_outstruct(&token_head);
	open_heredoc(&cmd, env);
	return (cmd);
}
