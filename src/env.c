/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:51:33 by vpelc             #+#    #+#             */
/*   Updated: 2024/09/18 18:02:32 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env_copy(char **env)
{
	t_env	*env_top;
	t_env	*env_node;
	int		i;
	int		len;

	i = 0;
	env_node = malloc(sizeof(t_env));
	env_top = env_node;
	while (env[i])
	{
		len = ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '='));
		env_node->var_name = ft_substr(env[i], 0, len);
		env_node->content = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (i == 0)
			env_node->next = NULL;
		else
			ft_lstlast(env_top)->next = env_node;
		
		i++;
	}
	
}
