/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command_supp.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/04 12:55:51 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_handle_child_sig(int err)
{
	if (err == 131)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "Quit: 3", 7);
		write(1, "\n", 1);
	}
	if (err == 130)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
	}
}

int	ft_exec_built_ins_in_pipe(t_command *cmd, t_program_data *data)
{
	if (cmd->output_fd != STDOUT_FILENO)
	{
		dup2(cmd->output_fd, STDOUT_FILENO);
		close(cmd->output_fd);
	}
	if (cmd->input_fd != STDIN_FILENO)
	{
		dup2(cmd->input_fd, STDIN_FILENO);
		close(cmd->input_fd);
	}
	return (ft_exec_built_ins(cmd, data));
}
