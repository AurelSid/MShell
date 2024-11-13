/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_supp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/13 14:50:33 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	iter_cpy(t_env **cpy, t_env **tmp, t_env **min, t_env **sort)
{
	while ((*cpy))
	{
		(*tmp) = (*cpy);
		(*min) = (*tmp);
		(*tmp) = (*tmp)->next;
		while ((*tmp))
		{
			if (strcmp((*min)->var_name, (*tmp)->var_name) > 0)
				(*min) = (*tmp);
			(*tmp) = (*tmp)->next;
		}
		if ((*min)->prev == NULL)
			(*cpy) = (*min)->next;
		else
			(*min)->prev->next = (*min)->next;
		if ((*min)->next != NULL)
			(*min)->next->prev = (*min)->prev;
		(*min)->prev = NULL;
		(*min)->next = NULL;
		if ((*sort) == NULL)
			(*sort) = (*min);
		else
			ft_add_env(sort, (*min));
	}
}

t_env	*ft_env_sort(t_env *env)
{
	t_env	*cpy;
	t_env	*tmp;
	t_env	*sort;
	t_env	*min;

	tmp = NULL;
	min = NULL;
	sort = NULL;
	cpy = ft_env_copy_2(env);
	iter_cpy(&cpy, &tmp, &min, &sort);
	return (sort);
}

void	ft_pwd_setup(t_env	**env, char *type)
{
	char	cwd[PATH_MAX];
	char	*tmp;

	if (ft_strcmp(type, "PWD") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)))
		{
			tmp = ft_strdup(cwd);
			free((*env)->content);
			(*env)->content = tmp;
		}
		else
			perror("pwd");
	}
	else if (ft_strcmp(type, "OLDPWD") == 0)
	{
		free((*env)->content);
		(*env)->content = NULL;
	}
}

void	ft_env_empty(void)
{
	t_env	*env_node;
	char	cwd[PATH_MAX];

	env_node = malloc(sizeof(t_env));
	env_node->var_name = ft_strdup("SHLVL");
	env_node->content = ft_strdup("1");
	env_node->next = NULL;
	env_node->prev = NULL;
	ft_add_env(&g_data.env, env_node);
	env_node = malloc(sizeof(t_env));
	env_node->var_name = ft_strdup("PWD");
	if (getcwd(cwd, sizeof(cwd)))
		env_node->content = ft_strdup(cwd);
	else
		perror("pwd");
	env_node->next = NULL;
	env_node->prev = NULL;
	ft_add_env(&g_data.env, env_node);
	env_node = malloc(sizeof(t_env));
	env_node->var_name = ft_strdup("OLDPWD");
	env_node->content = NULL;
	env_node->next = NULL;
	env_node->prev = NULL;
	ft_add_env(&g_data.env, env_node);
}
