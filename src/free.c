/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:24:24 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/16 14:59:31 by vpelc            ###   ########.fr       */
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
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
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
