/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:51:33 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/16 14:09:22 by asideris         ###   ########.fr       */
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
	new->prev = current;
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
		env_node->prev = NULL;
		if (i == 0)
			data->env = env_node;
		else
			ft_add_env(&data->env, env_node);
		i++;
	}
	return (0);
}

t_env	*ft_env_copy_2(t_env *env)
{
	t_env	*env_cpy;
	t_env	*env_node;

	while (env)
	{
		env_node = malloc(sizeof(t_env));
		env_node->var_name = ft_strdup(env->var_name);
		env_node->content = ft_strdup(env->content);
		env_node->next = NULL;
		env_node->prev = NULL;
		if (env->prev == NULL)
			env_cpy = env_node;
		else
			ft_add_env(&env_cpy, env_node);
		env = env->next;
	}
	return (env_cpy);
}
