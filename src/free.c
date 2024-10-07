/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:24:24 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/07 18:27:49 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		free(env->var_name);
		env->var_name = NULL;
		free(env->content);
		env->content = NULL;
		temp = env->next;
		free(env);
		env = temp;
	}
}
