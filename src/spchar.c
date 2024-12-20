/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spchar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:30:37 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/14 13:27:19 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_check_exitsp(char *arg)
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
	end = ft_strjoin(start, ft_itoa(ft_return_data()->exit_status));
	end = ft_strjoin(end, (tmp + 2));
	free(arg);
	free(start);
	return (end);
}

int	ft_switchspchar(int i, char **to_check, char *tmp)
{
	int		j;
	char	*sub;

	j = 0;
	if (tmp[i] == '\"')
	{
		j = ft_handle_quotes(tmp, i);
		sub = ft_substr(tmp, i, j);
		*to_check = ft_spcharloop(sub);
	}
	else
	{
		j = ft_handle_words(tmp, i);
		sub = ft_substr(tmp, i, j);
		*to_check = ft_spcharloop(sub);
	}
	return (j);
}

void	ft_checkspchar(char **var)
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
			j = ft_switchspchar(i, &to_check, tmp);
		*var = ft_strdup(ft_strjoin_free(*var, to_check));
		i += j;
	}
	free(tmp);
	free(to_check);
}
