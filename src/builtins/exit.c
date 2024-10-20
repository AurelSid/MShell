/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:17:09 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/16 17:52:20 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_command *cmd, t_program_data data)
{
	int	args;

	if (data.command_top->next == NULL)
		printf("exit\n");
	if (!cmd->args)
		args = 0;
	else
	{
		args = atol(cmd->args);
		if (args > 255)
			args = (unsigned char)args;
	}
	exit(args);
}
