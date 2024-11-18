/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_supp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/18 18:39:48 by vpelc            ###   ########.fr       */
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

void	ft_pwd_setup(t_env **env, char *type)
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
	if (!ft_search_env_2("SHLVL"))
		add_shlvl();
	if (!ft_search_env_2("PWD"))	
		add_pwd();
	if (!ft_search_env_2("OLDPWD"))
		add_oldpwd();
}
