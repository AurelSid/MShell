/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:16:14 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/13 15:15:08 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_trimloop(char ***split)
{
	int		i;
	char	*result;

	i = 0;
	while ((*split)[i])
	{
		result = ft_strtrim_args((*split)[i], 0);
		free((*split)[i]);
		(*split)[i] = ft_strdup(result);
		free(result);
		i++;
	}
}

char	*ft_strtrim_args(char *str, int i)
{
	char		*trim;
	static char	*result;
	int			j;

	while (str && str[i])
	{
		j = 0;
		if (str[i] == '\'' || str[i] == '\"')
		{
			j = ft_handle_quotes(str, i);
			trim = ft_substr(str, i + 1, j - 2);
		}
		else
		{
			j = ft_handle_words(str, i);
			trim = ft_substr(str, i, j);
		}
		if (!result)
			result = ft_strdup(trim);
		else
			result = ft_strjoin_free(result, trim);
		free(trim);
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
