/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spchar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:30:37 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/24 16:09:40 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_spcharloop(char *args, t_program_data *data)
{
	char	*sub;
	char	*tmp;

	sub = ft_strchr(args, '$');
	tmp = NULL;
	while (sub && ft_strcmp(sub, tmp))
	{
		tmp = sub;
		if (args[0] == '\"')
			args = ft_db_quotes(args, data);
		else
			args = ft_spchar(args, data);
		args = ft_check_exitsp(args, *data);
		sub = ft_strchr(args, '$');
	}
	return (args);
}

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
	while (tmp[i] && tmp[i] != ' ' && tmp[i] != '$')
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

int	ft_switchspchar(int i, char **to_check, char *tmp, t_program_data *data)
{
	int		j;
	char	*sub;

	j = 0;
	if (tmp[i] == '\"')
	{
		j = ft_handle_quotes(tmp, i);
		sub = ft_substr(tmp, i, j);
		*to_check = ft_spcharloop(sub, data);
	}
	else
	{
		j = ft_handle_words(tmp, i);
		sub = ft_substr(tmp, i, j);
		*to_check = ft_spcharloop(sub, data);
	}
	//*to_check = ft_check_exitsp(*to_check, *data);
	//free(sub);
	return (j);
}

void	ft_checkspchar(char **var, t_program_data *data)
{
	char	*tmp;
	char	*to_check;
	int		i;
	int		j;

	i = 0;
	to_check = NULL;
	tmp = *var;
	*var = NULL;
	while (tmp[i])
	{
		j = 0;
		if (tmp[i] == '\'')
		{
			j = ft_handle_quotes(tmp, i);
			to_check = ft_substr(tmp, i, j);
		}
		else
			j = ft_switchspchar(i, &to_check, tmp, data);
		*var = ft_strdup(ft_strjoin_free(*var, to_check));
		i += j;
	}
	free(to_check);
}
