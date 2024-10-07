/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:16:09 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/07 14:41:55 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_check_opt(char *opt)
{
	int		i;
	int		j;
	char	**opts;

	i = 0;
	if (!opt[i])
		return (1);
	opts = ft_split(opt, ' ');
	while (opts[i])
	{
		j = 1;
		while (opts[i][j])
		{
			if (opts[i][j] != 'n')
				return (1);
			j++;
		}
		i++;
	}

	return (0);
}

static char	*ft_check_spchar(char *arg, t_program_data data)
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

void	ft_echo(char *arg, char *opt, t_program_data data)
{
	int		i;
	char	**args;

	i = 0;
	args = ft_split(arg, ' ');
	while (args[i])
	{
		if (i != 0)
			printf(" ");
		args[i] = ft_check_spchar(args[i], data);
		printf("%s", args[i]);
		i++;
	}
	if (ft_check_opt(opt))
		printf("\n");
	ft_free_split(args);
}
