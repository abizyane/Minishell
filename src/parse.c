/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 15:00:35 by abizyane          #+#    #+#             */
/*   Updated: 2023/07/12 16:24:03 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_redir_fname(t_cmdline **head, char *file_name)
{
	t_cmdline	*tmp;
	t_redir		*r_tmp;

	tmp = last_command(*head);
	r_tmp = last_redir(tmp->redir);
	r_tmp->filename = file_name;
}

void	add_args(t_cmdline **head, char *token)
{
	t_cmdline	*tmp;
	int 		i;

	tmp = last_command(*head);
	i = 1;

	while (tmp->args && tmp->args[i] != 0)
		i++;
	tmp->args[i] = ft_strdup(token);
}

int	count_args(t_token **head)
{
	t_token	*tmp;
	int	i;

	i = 0;
	tmp = *head;
	while (tmp && tmp->type != Pipe)
	{
		i++;
		tmp = tmp->nxt;
	}
	return (i + 1);
}

void	add_redir(t_cmdline **head, t_token *token) //TODO: redirections before commands cause problems
{
	t_cmdline	*tmp;

	tmp = last_command(*head);
	lstadd_redir(&tmp->redir, token);
}


t_cmdline	*fill_outstruct(t_token **head)
{
	t_cmdline	*cmd;
    t_token		*token;
	int			cmd_args;

	token = *head;
	cmd = lstnew_command(NULL, 0);
	while (token)
	{
		if (token->type == Cmd)
		{
			cmd_args = count_args(&token);
			lstadd_command(&cmd, token->line, cmd_args);
		}
		else if (token->type == Fname)
			add_redir_fname(&cmd, token->line);
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

void	get_type2(t_token **head)
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

t_cmdline	*parse_line(char *line)
{
	t_token 	*token_head;
    t_cmdline	*cmd = NULL;
//	char *tok[10] = {"WORD", "PIPE", "IN", "HER", "OUT", "APP", "SPA", "CMD", "ARG", "FNAME"};

	token_head = tokenizer(line);
	expand_env_var(&token_head);
	remove_quotes(&token_head);
	get_type2(&token_head);
	cmd = fill_outstruct(&token_head);
	open_heredoc(&cmd);
//	int i = 1;
//	while (token_head)
//	{
//		printf("token n* %d == %s ====== type == %s \n", i++, token_head->line,
//				tok[token_head->type - 1]);
//		token_head = token_head->nxt;
//	}
	return (cmd);
}