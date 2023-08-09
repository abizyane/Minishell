/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abizyane <abizyane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 02:27:16 by ahamrad           #+#    #+#             */
/*   Updated: 2023/08/09 06:58:45 by abizyane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int unset(t_env **env, char *key)
{
	t_env	*var;
	
	var = find_env(*env, key);
	if (var->content)
	{	
		free (var->content);
		var->content = NULL;
		if (new_var[1])
			var->content = new_var[1];
		return ;
	}
	else 
	{
		if (new_var[1])
			var->content = ft_strdup(new_var[1]);
		else
			var->content = ft_strdup("");
	}
}