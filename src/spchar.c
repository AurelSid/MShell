/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spchar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:30:37 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/21 18:16:43 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_handle_words(char *var, int index)
{
	int	i;

	i = index;
	while (var[i] && (var[i] != ' ' && var[i] != '\'' && var[i] != '\"'
			&& var[i] != '>' && var[i] != '<'))
		i++;
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
	if (!tmp[i] || tmp[i] == '?')
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

char	*ft_check_exitsp(char *arg, t_program_data data)
{
	char	*start;
	char	*end;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strchr(arg, '$');
	if (!tmp || (tmp[1]) != '?')
		return (arg);
	start = ft_substr(arg, 0, ft_strlen(arg) - (ft_strlen(tmp)));
	end = ft_strjoin(start, ft_itoa(data.exit_status));
	end = ft_strjoin(end, (tmp + 2));
	free(arg);
	free(start);
	return (end);
}

int	ft_switchspchar(int i, char **to_check, char *tmp, int trim)
{
	int	j;

	j = 0;
	if (tmp[i] == '\"')
	{
		j = ft_handle_quotes(tmp, i);
		*to_check = ft_db_quotes(ft_substr(tmp, i, j), &data);
	}
	else
	{
		j = ft_handle_words(tmp, i);
		*to_check = ft_spchar(ft_substr(tmp, i, j), &data);
	}
	*to_check = ft_check_exitsp(*to_check, data);
	if (trim)
		*to_check = ft_strtrim_free(*to_check, "\"");
	return (j);
}

void	ft_checkspchar(char **var, int trim)
{
	char	*tmp;
	char	*to_check;
	int		i;
	int		j;

	i = -1;
	tmp = *var;
	*var = NULL;
	to_check = NULL;
	while (tmp[++i])
	{
		j = 0;
		if (tmp[i] == '\'')
		{
			j = ft_handle_quotes(tmp, i);
			if (trim)
				to_check = ft_strtrim_free(ft_substr(tmp, i, j), "\'");
			*var = ft_strdup(ft_strjoin_free(*var, to_check));
			i += j - 1;
			continue ;
		}
		else
			j = ft_switchspchar(i, &to_check, tmp, trim);
		*var = ft_strdup(ft_strjoin_free(*var, to_check));
		i += j - 1;
	}
	free(to_check);
}
