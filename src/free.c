/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:24:24 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/01 16:35:00 by vpelc            ###   ########.fr       */
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
	t_env	*tmp;

	tmp = env->next;
	while (env)
	{
		free(env->var_name);
		free(env->content);
		free(env);
		env = NULL;
		env = tmp;
		if (env->next)
			tmp = tmp->next;
	}
}
