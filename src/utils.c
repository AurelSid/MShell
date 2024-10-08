/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:16:14 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/08 12:55:42 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	send_error(char *error)
{
	write(2, "\033[1;31mError!\033[0m", 17);
	write(2, error, ft_strlen(error));
	exit(1);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	join = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (free(s1), NULL);
	i = -1;
	while (s1 && s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s1 && s2[++j])
		join[i + j] = s2[j];
	join[i + j] = '\0';
	return (free(s1), join);
}

/*	LEAKS ON ENV COPY	*/
t_env	*ft_env_sort(t_env *env)
{
	t_env	*cpy;
	t_env	*tmp;
	t_env	*sort;
	t_env	*min;

	cpy = ft_env_copy_2(env);
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
	//free(cpy);
	return (sort);
}
