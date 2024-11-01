/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_supp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/01 15:29:22 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	iter_cpy(t_env *cpy, t_env *tmp, t_env *min, t_env *sort)
{
	while (cpy)
	{
		tmp = cpy;
		min = tmp;
		tmp = tmp->next;
		while (tmp)
		{
			if (strcmp(min->var_name, tmp->var_name) > 0)
				min = tmp;
			tmp = tmp->next;
		}
		if (min->prev == NULL)
			cpy = min->next;
		else
			min->prev->next = min->next;
		if (min->next != NULL)
			min->next->prev = min->prev;
		min->prev = NULL;
		min->next = NULL;
		if (sort == NULL)
			sort = min;
		else
			ft_add_env(&sort, min);
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
	iter_cpy(cpy, tmp, min, sort);
	return (sort);
}
