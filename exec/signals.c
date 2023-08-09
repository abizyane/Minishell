/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:36:35 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/09 17:32:55 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_int(int sig)
{
	if (sig == SIGINT)
	{
		write (1, "\n", 1);
		if (rl == 0)
		{
			exit_status = 1;
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	sig_handler(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sig_int);
	signal(SIGQUIT, SIG_IGN);
}
