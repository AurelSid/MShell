/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:43:33 by asideris          #+#    #+#             */
/*   Updated: 2024/10/14 18:47:34 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	sizes1;
	size_t	sizes2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sizes1 = ft_strlen(s1);
	sizes2 = ft_strlen(s2);
	s = malloc(sizeof(char) * (sizes1 + sizes2 + 1));
	if (!s)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s[j + i] = s2[j];
		j++;
	}
	s[j + i] = '\0';
	return (s);
}
