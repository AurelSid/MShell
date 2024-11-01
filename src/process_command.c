/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:45:54 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/01 17:26:15 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	process_command_loop(t_program_data *data, t_command **tmp_cmd)
{
	while ((*tmp_cmd))
	{
		if ((*tmp_cmd)->redirection_list == NULL)
			dup2(data->original_stdout, STDOUT_FILENO);
		if (ft_apply_redir((*tmp_cmd), data))
		{
			if ((*tmp_cmd)->next)
			{
				(*tmp_cmd)->ok = -1;
				(*tmp_cmd) = (*tmp_cmd)->next;
				continue ;
			}
			else
				return (1);
		}
		(*tmp_cmd) = (*tmp_cmd)->next;
	}
	return (0);
}

void	process_command(t_program_data *data, char **env)
{
	t_command	*tmp_cmd;

	tmp_cmd = data->command_top;
	if (process_command_loop(data, &tmp_cmd))
		return ;
	tmp_cmd = data->command_top;
	while (tmp_cmd)
	{
		ft_last_redir(tmp_cmd->last_in, tmp_cmd->last_out, tmp_cmd, data);
		if (tmp_cmd->name != NULL)
		{
			if (tmp_cmd->ok == 0)
			{
				ft_exec(tmp_cmd, env, data);
				data->exit_status = 0;
			}
			else
			{
				setup_pipe_and_redirect();
				ft_exec(tmp_cmd, env, data);
			}
		}
		tmp_cmd = tmp_cmd->next;
	}
}
