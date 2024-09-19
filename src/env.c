/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:51:33 by vpelc             #+#    #+#             */
/*   Updated: 2024/09/19 14:32:09 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_add_env(t_env **lst, t_env *new)
{
	t_env	*current;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

int	ft_env_copy(char **env, t_program_data *data)
{
	t_env	*env_node;
	int		i;
	int		len;

	i = 0;
	while (env[i])
	{
		env_node = malloc(sizeof(t_env));
		len = ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '='));
		env_node->var_name = ft_substr(env[i], 0, len);
		env_node->content = ft_strdup(ft_strchr(env[i], '=') + 1);
		env_node->next = NULL;
		if (i == 0)
			data->env = env_node;
		else
			ft_add_env(&data->env, env_node);
		i++;
		//printf("%s : %s\n", env_node->var_name, env_node->content);
		//printf("top : %p, current : %p\n", data->env, env_node);
	}
	return (0);
}
