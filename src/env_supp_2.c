/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_supp_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:24:39 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/18 18:28:21 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_shlvl(void)
{
	t_env	*env_node;
	
	env_node = malloc(sizeof(t_env));
	env_node->var_name = ft_strdup("SHLVL");
	env_node->content = ft_strdup("1");
	env_node->next = NULL;
	env_node->prev = NULL;
	ft_add_env(&ft_return_data()->env, env_node);
}

void	add_pwd(void)
{
	t_env	*env_node;
	char	cwd[PATH_MAX];

	env_node = malloc(sizeof(t_env));
	env_node->var_name = ft_strdup("PWD");
	if (getcwd(cwd, sizeof(cwd)))
		env_node->content = ft_strdup(cwd);
	else
		perror("pwd");
	env_node->next = NULL;
	env_node->prev = NULL;
	ft_add_env(&ft_return_data()->env, env_node);
}

void	add_oldpwd(void)
{
	t_env	*env_node;
	
	env_node = malloc(sizeof(t_env));
	env_node->var_name = ft_strdup("OLDPWD");
	env_node->content = NULL;
	env_node->next = NULL;
	env_node->prev = NULL;
	ft_add_env(&ft_return_data()->env, env_node);
}