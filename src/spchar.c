/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spchar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:30:37 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/18 13:32:26 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_handle_words_2(char *var, int index)
{
	int	i;

	i = index;
	while (var[i] && (var[i] != ' ' && var[i] != '\'' && var[i] != '\"'))
		i++;
	return (i - index);
}

int	ft_handle_quotes_2(char *var, int index)
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
	/*  ---> no error but skip the command */
	return (i - index);
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
	if (tmp[i] == '?')
		return (var);
	while (tmp[i] && tmp[i] != ' ')
		i++;
	found = ft_substr(tmp, 0, i);
	if (ft_search_env(&found, *data) == 0)
		found = NULL;
	start = ft_substr(var, 0, ft_strlen(var) - (ft_strlen(tmp) + 1));
	end = ft_strjoin_free(start, found);
	end = ft_strjoin_free(end, (tmp + i));
	free(var);
//	free(found);
	return (end);
}

int	ft_switchspchar(int j, char **to_check, t_program_data *data)
{
	 if (tmp[i] == '\"')
	{
		j = ft_handle_quotes_2(tmp, i);
		*to_check = ft_db_quotes(ft_substr(tmp, i, j), data);
	}
	else
	{
		j = ft_handle_words_2(tmp, i);
		*to_check = ft_spchar(ft_substr(tmp, i, j), data);
	}
	return (j);
}

void	ft_checkspchar(char **var, t_program_data *data)
{
	char	*tmp;
	char	*to_check;
	int		i;
	int		j;

	i = -1;
	tmp = *var;
	*var = NULL;
	while (tmp[++i])
	{
		j = 0;
		if (tmp[i] == '\'')
		{
			i = ft_handle_quotes_2(tmp, i);
			continue ;
		}
		else if (tmp[i] == '\"')
		{
			j = ft_handle_quotes_2(tmp, i);
			to_check = ft_db_quotes(ft_substr(tmp, i, j), data);
		}
		else
		{
			j = ft_handle_words_2(tmp, i);
			to_check = ft_spchar(ft_substr(tmp, i, j), data);
		}
		to_check = ft_strtrim_free(to_check, "\"");
		*var = ft_strdup(ft_strjoin_free(*var, to_check));
		i += j - 1;
	}
	free(to_check);
}
