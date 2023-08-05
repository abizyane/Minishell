/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:18:35 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/05 17:12:28 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    *get_homeuuu(t_env *env)
{
    t_env   *tmp;

    tmp = env;
    while (tmp)
    {
        if (ft_strcmp(tmp->content, "HOME") == 0)
            return (tmp->content);
        tmp = tmp->next;
    }
    return (NULL);
}


int     cd(t_cmdline *cmd, t_env *env)
{
    char    *home;

    if (!cmd->args[1])
    {
        home = get_home(env);
        if (chdir(home) == -1)
            printf("bash: cd: HOME not set\n");
    }
    return (EXIT_FAILURE);
}