/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:16:14 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/31 15:14:23 by asideris         ###   ########.fr       */
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
	while (s1 && s2[++j])
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

void	ft_trimloop(char ***split)
{
	int		i;
	char	*result;

	i = 0;
	while ((*split)[i])
	{
		result = ft_strtrim_args((*split)[i]);
		free((*split)[i]);
		(*split)[i] = ft_strdup(result);
		i++;
	}
}

char	*ft_strtrim_args(char *str)
{
	char	*trim;
	char	*result;
	int		i;
	int		j;

	i = 0;
	result = NULL;
	while (str[i])
	{
		j = 0;
		if (str[i] == '\'' || str[i] == '\"')
		{
			j = ft_handle_quotes(str, i);
			trim = ft_substr(str, i + 1, j - 2);
			result = ft_strjoin_free(result, trim);
		}
		else
		{
			j = ft_handle_words(str, i);
			trim = ft_substr(str, i, j);
			result = ft_strjoin_free(result, trim);
		}
		i += j;
	}
	return (result);
}

void	ft_export_trim(char ***args)
{
	int		i;
	int		len;
	char	*sub;

	i = 0;
	while ((*args)[i])
	{
		len = ft_strlen((*args)[i]);
		while (((*args)[i][0] == '\'' && (*args)[i][len - 1] == '\'')
			|| ((*args)[i][0] == '\"' && (*args)[i][len - 1] == '\"'))
		{
			sub = ft_substr((*args)[i], i + 1, len - 2);
			(*args)[i] = ft_strdup(sub);
			free(sub);
			len = ft_strlen((*args)[i]);
		}
		i++;
	}
}
