/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:16:14 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/09 17:51:24 by vpelc            ###   ########.fr       */
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

	sort = NULL;
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

char	*ft_spchar(char *var, t_program_data *data)
{
	char	*found;
	char	*start;
	char	*end;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strchr(var, '$');
	if (!tmp)
		return (var);
	tmp += 1;
	while (tmp[i] != ' ' && tmp[i])
		i++;
	found = ft_substr(tmp, 0, i);
	if (ft_search_env(&found, *data) == 0)
		found = NULL;
	start = ft_substr(var, 0, ft_strlen(var)
			- (ft_strlen(tmp) + 1));
	end = ft_strjoin_free(start, found);
	end = ft_strjoin_free(end, (tmp + i));
	//free(start);
	free(var);
	//free(found);
	return (end);
}
