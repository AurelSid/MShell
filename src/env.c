/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:51:33 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/18 18:35:54 by vpelc            ###   ########.fr       */
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

char	*ft_check_lvl(char *content)
{
	int	val;

	val = ft_atoi(content);
	if (INT_MIN <= val && val < 0)
		return (ft_itoa(0));
	else if (val < INT_MIN)
		return (ft_itoa(1));
	else if (0 <= val && val < 999)
		return (ft_itoa(val + 1));
	else if (val >= 1000)
		return (ft_itoa(1));
	else if (val == 999)
		return ("");
	else
		return ("");
}

void	ft_env_copy_supp(int i, t_env **env_node)
{
	(*env_node)->next = NULL;
	(*env_node)->prev = NULL;
	if (i == 0)
		ft_return_data()->env = (*env_node);
	else
		ft_add_env(&ft_return_data()->env, (*env_node));
}

int	ft_env_copy(char **env)
{
	t_env	*env_node;
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		env_node = malloc(sizeof(t_env));
		len = ft_strlen(env[i]) - ft_strlen(ft_strchr(env[i], '='));
		env_node->var_name = ft_substr(env[i], 0, len);
		env_node->content = ft_strdup(ft_strchr(env[i], '=') + 1);
		if (ft_strcmp(env_node->var_name, "PWD") == 0
			|| ft_strcmp(env_node->var_name, "OLDPWD") == 0)
			ft_pwd_setup(&env_node, env_node->var_name);
		if (ft_strcmp(env_node->var_name, "SHLVL") == 0)
		{
			tmp = ft_check_lvl(env_node->content);
			free(env_node->content);
			env_node->content = tmp;
		}
		ft_env_copy_supp(i, &env_node);
	}
	ft_env_empty();
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
		if (env->content)
			env_node->content = ft_strdup(env->content);
		else
			env_node->content = NULL;
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
