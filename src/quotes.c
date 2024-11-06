/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:17:00 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/06 16:04:33 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

int	ft_search_env(char **var, t_program_data data)
{
	t_env	*tmp;

	tmp = data.env;
	while (tmp)
	{
		if ((ft_strcmp(*var, tmp->var_name) == 0))
		{
			*var = tmp->content;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_handle_quotes(char *var, int index)
{
	int		i;
	char	type;

	type = var[index];
	i = index;
	i++;
	while (var[i] != type && var[i])
		i++;
	i++;
	if (i > (int)ft_strlen(var))
		return (-1);
	return (i - index);
}

char	*ft_db_quotes(char *token, t_program_data *data)
{
	char	*found;
	char	*start;
	char	*end;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strchr(token, '$');
	if (!tmp)
		return (token);
	tmp += 1;
	if (!tmp[i] || tmp[i] == '?' || tmp[i] == ' ' || tmp[i] == '\"')
		return (token);
	while (tmp[i] && tmp[i] != ' ' && tmp[i] != '\"' && tmp[i] != '$')
		i++;
	found = ft_substr(tmp, 0, i);
	if (ft_search_env(&found, *data) == 0)
		found = NULL;
	start = ft_substr(token, 0, ft_strlen(token) - (ft_strlen(tmp) + 1));
	end = ft_strjoin_free(start, found);
	end = ft_strjoin_free(end, (tmp + i));
	free(token);
	return (end);
}
