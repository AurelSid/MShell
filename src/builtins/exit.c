/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:17:09 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/18 17:50:30 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_exit(t_command *cmd, t_program_data data)
{
	int	args;

	if (data.command_top->next == NULL)
		printf("exit\n");
	if (cmd->args[0])
		args = atol(cmd->args);
	else if (cmd->options[0])
		args = atol(cmd->options);
	else
		args = 0;
	if (args > 255)
		args = (unsigned char)args;
	exit(args);
}
