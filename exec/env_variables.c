/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamrad <ahamrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 03:59:35 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/05 06:58:50 by ahamrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env   *env_new(char *name, char *content)
{
    t_env   *new;

    new = ft_calloc(1, sizeof(t_env));
    if (!new)
        return (NULL);
    new->name = name;
    new->content = content;
    new->next = NULL;
    return (new);
}

t_env   *env_add_back(t_env **env, t_env *new_env)
{
    t_env   *tmp;

    tmp = *env;
    if (!tmp)
        *(env) = new_env;
    else
    {
        while (tmp && tmp->next)
            tmp = tmp->next;
        tmp->next = new_env;
    }
}

t_env   *array_to_list(char **envp)
{
    char    **tab;
    t_env   *envs;
    int     i = 0;

    while (envp[i])
    {
                         
    }
}






