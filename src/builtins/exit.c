/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:17:09 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/02 12:35:49 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(char *arg)
{
	int	args;

	printf("exit\n");
	if (!arg)
		args = 0;
	else
	{
		args = atol(arg);
		if (args > 255)
			args = (unsigned char)args;
	}
	exit(args);
}
