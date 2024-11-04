/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/04 12:51:14 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_files_loop(t_redirection *redir, t_program_data *data, t_command *cmd)
{
	while (redir)
	{
		if (redir->type == REDIRECT_IN)
		{
			if (ft_handle_redirect_in(cmd, redir, data) == -1)
				return (-1);
		}
		else if (redir->type == REDIRECT_OUT)
		{
			if (ft_handle_redirect_out(cmd, redir, data) == -1)
				return (-1);
		}
		else if (redir->type == REDIRECT_APPEND)
		{
			if (ft_handle_redirect_append(cmd, redir, data) == -1)
				return (-1);
		}
		else if (redir->type == REDIRECT_HEREDOC)
		{
			ft_handle_heredoc(redir, cmd, data);
		}
		redir = redir->next;
	}
	return (0);
}

int	ft_open_file(t_command *cmd, t_program_data *data)
{
	t_redirection	*redir;

	redir = cmd->redirection_list;
	if (open_files_loop(redir, data, cmd) == -1)
	{
		return (-1);
	}
	return (1);
}
