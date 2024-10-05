/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:16:09 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/03 15:46:46 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_check_opt(char *opt)
{
	int	i;

	i = 0;
	if (opt[i] != '-')
		return (1);
	i++;
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo(char *arg, char *opt)
{
	int		i;
	char	**args;

	i = 0;
	args = ft_split(arg, ' ');
	while (args[i])
	{
		printf("%s ", args[i]);
		i++;
	}
	if (ft_check_opt(opt))
		printf("\n");
	ft_free_split(args);
}
