/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:45:54 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/12 16:12:26 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	process_command_loop(t_command **tmp_cmd)
{
	while ((*tmp_cmd))
	{
		if ((*tmp_cmd)->redirection_list == NULL)
			dup2(g_data.original_stdout, STDOUT_FILENO);
		if (ft_apply_redir((*tmp_cmd)))
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

int	supp_pc(t_command **tmp_cmd, char **env)
{
	ft_last_redir((*tmp_cmd)->last_in, (*tmp_cmd)->last_out, *tmp_cmd);
	if ((*tmp_cmd)->name != NULL)
	{
		if ((*tmp_cmd)->ok == 0)
		{
			if (g_data.sig_int > 0)
				return (1);
			ft_exec(*tmp_cmd, env);
			g_data.exit_status = 0;
		}
		else
		{
			if (g_data.sig_int > 0)
				return (1);
			setup_pipe_and_redirect();
			ft_exec(*tmp_cmd, env);
		}
	}
	return (0);
}

void	process_command(char **env)
{
	t_command	*tmp_cmd;

	tmp_cmd = g_data.command_top;
	if (process_command_loop(&tmp_cmd))
		return ;
	tmp_cmd = g_data.command_top;
	while (tmp_cmd)
	{
		if (supp_pc(&tmp_cmd, env))
			return ;
		tmp_cmd = tmp_cmd->next;
	}
}
