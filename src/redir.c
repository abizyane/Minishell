/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 04:37:02 by abizyane          #+#    #+#             */
/*   Updated: 2023/07/21 13:49:03 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//void	add_redir_fname(t_cmdline **head, char *file_name)
//{
//	t_cmdline	*tmp;
//	t_redir		*r_tmp;
//
//	tmp = last_command(*head);
//	r_tmp = last_redir(tmp->redir);
//	r_tmp->filename = file_name;
//}
//
//void	add_redir(t_cmdline **head, t_token *token)
//{
//	t_cmdline	*tmp;
//
//	tmp = last_command(*head);
//	lstadd_redir(&tmp->redir, token);
//}

//void	get_type2(t_token **head)
//{
//	t_token	*token;
//
//	token = (*head);
//	while (token)
//	{
//		if (token->type == Word && (!token->prv || (token->prv && token->prv->type == Pipe)))
//			token->type = Cmd;
//		else if (token->type == Word && (token->prv->type == Cmd || token->prv->type == Arg || token->prv->type == Fname))
//			token->type = Arg;
//		else if (token->type == Word)
//			token->type = Fname;
//		token = token->nxt;
//	}
//}