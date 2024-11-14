/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spchar_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/12 16:14:00 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_spcharloop(char *args)
{
	char	*sub;
	char	*tmp;

	sub = ft_strchr(args, '$');
	tmp = NULL;
	while (sub && ft_strcmp(sub, tmp))
	{
		tmp = sub;
		if (args[0] == '\"')
			args = ft_db_quotes(args);
		else
			args = ft_spchar(args);
		args = ft_check_exitsp(args);
		sub = ft_strchr(args, '$');
	}
	return (args);
}

int	ft_handle_words(char *var, int index)
{
	int	i;

	i = index;
	while (var[i] && (var[i] != ' ' && var[i] != '\'' && var[i] != '\"'
			&& var[i] != '>' && var[i] != '<' && var[i] != '|'))
		i++;
	return (i - index);
}

char	*ft_spchar(char *var)
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
	if (ft_search_env(&found) == 0)
		found = NULL;
	start = ft_substr(var, 0, ft_strlen(var) - (ft_strlen(tmp) + 1));
	end = ft_strjoin_free(start, found);
	end = ft_strjoin_free(end, (tmp + i));
	free(var);
	return (end);
}
