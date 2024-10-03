/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:16:09 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/03 15:44:43 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_echo(char **arg, char *opt)
{
	int	i;

	i = 0;
	if (ft_strcmp(opt, "-n") != 0)
	{
		while (arg[i])
		{
			printf("%s\n", arg[i]);
			i++;
		}
	}
	else
	{
		while (arg[i])
		{
			printf("%s", arg[i]);
			i++;
		}
	}
}
