/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:16:14 by vpelc             #+#    #+#             */
/*   Updated: 2024/09/23 20:05:10 by vpelc            ###   ########.fr       */
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
		return (free(&s1), NULL);
	i = -1;
	while (s1 && s1[++i])
		join[i] = s1[i];
	j = -1;
	while (s1 && s2[++j])
		join[i + j] = s2[j];
	join[i + j] = '\0';
	return (free(&s1), join);
}
