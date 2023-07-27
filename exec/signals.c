/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:36:35 by ahamrad           #+#    #+#             */
/*   Updated: 2023/07/27 22:16:40 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    ignore_sigquit(void)
{
    struct sigaction action;

    action.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &action, NULL);
}

void    sigint_handler(int signo)
{
    (void)signo;
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    handle_signals(void)
{
    struct sigaction action;

    ignore_sigquit();
    action.sa_handler = sigint_handler;
    sigaction(SIGINT, &action, NULL);
}