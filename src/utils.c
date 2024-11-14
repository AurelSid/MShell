/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:16:14 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/13 14:49:45 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	while (s2 && s2[++j])
		join[i + j] = s2[j];
	join[i + j] = '\0';
	return (free(s1), join);
}

static int	ft_check_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim_free(char *s1, char *set)
{
	char	*cpy;
	size_t	i;
	size_t	j;
	size_t	k;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (s1[i] && ft_check_set(s1[i], set))
		i++;
	j = ft_strlen(s1);
	while (j > i && ft_check_set(s1[j - 1], set))
		j--;
	cpy = malloc(sizeof(char) * ((j - i) + 1));
	if (!cpy)
		return (0);
	k = 0;
	while (i + k < j)
	{
		cpy[k] = s1[i + k];
		k++;
	}
	cpy[k] = '\0';
	return (free(s1), cpy);
}
