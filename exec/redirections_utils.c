/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 02:59:35 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/12 03:00:20 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirection_check_out(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (redir->type == redApp || redir->type == redOut)
			return (1);
		else
			tmp = tmp->nxt;
	}
	return (0);
}

int	redirection_check_in(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (redir->type == redIn || redir->type == Heredoc)
			return (1);
		else
			tmp = tmp->nxt;
	}
	return (0);
}
