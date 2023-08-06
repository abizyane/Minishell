/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 03:59:35 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/06 19:32:53 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env   *env_new(char *key, char *content)
{
    t_env   *new;

    new = ft_calloc(1, sizeof(t_env));
    if (!new)
        return (NULL);
    new->key = key;
    new->content = content;
    new->nxt = NULL;
    return (new);
}

void	env_add_back(t_env **env_head, char	**env_var)
{
    t_env   *tmp;
	t_env	*new_env;

    tmp = *env_head;
	new_env = env_new(env_var[0], env_var[1]);
    if (!tmp)
        *(env_head) = new_env;
    else
    {
        while (tmp && tmp->nxt)
            tmp = tmp->nxt;
        tmp->nxt = new_env;
    }
}

t_env	*lst_env(char **env)
{
    int		i;
    t_env	*head;
    char	**str;

    i = 0;
    head = NULL;
    while (env && env[i])
    {
    	str = ft_split(env[i], '=');
		env_add_back(&head, str);
		free(str);
		i++;
    }
    return (head);
}

t_env   *create_env(void);
// {
//     t_env   *head;
    
    
//     return (head);
// }

char	*find_var(t_env *head, char *env_var)
{
    t_env	*tmp;

    tmp = head;
    while (tmp)
    {
        if (ft_strcmp(tmp->key, env_var) == 0)
			return (tmp->content);
        tmp = tmp->nxt;
    }
    return (NULL);
}

