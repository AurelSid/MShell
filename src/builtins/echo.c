/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:16:09 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/18 16:18:32 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* static int	ft_check_opt(char *opt)
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
	ft_free_split(opts);
	return (0);
} */

static int	ft_valid_opt(char *opt)
{
	int	i;

	i = 1;
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_check_opt(char *opt, char *arg)
{
	int		i;
	int		result;
	char	**opts;

	i = 0;
	result = 1;
	if (!opt)
		return (1);
	opts = ft_split(opt, ' ');
	while (opts[i])
	{
		if (ft_valid_opt(opts[i]))
		{
			while (opts[i])
			{
				printf("%s", opts[i++]);
				if (opts[i] || arg[0])
					printf(" ");
			}
			return (result);
		}
		result = 0;
		i++;
	}
	return (ft_free_split(opts), result);
}

void	ft_echo(t_command *cmd)
{
	int		i;
	int		opt_i;
	char	**args;

	i = 0;
	args = ft_split(cmd->args, ' ');
	opt_i = ft_check_opt(cmd->options, cmd->args);
	while (args[i])
	{
		if (i != 0)
			printf(" ");
		printf("%s", args[i]);
		i++;
	}
	if (opt_i)
		printf("\n");
	ft_free_split(args);
}
