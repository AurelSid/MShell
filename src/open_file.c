/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/12 16:11:04 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_files_loop(t_redirection *redir, t_command *cmd)
{
	while (redir)
	{
		if (redir->type == REDIRECT_IN)
		{
			if (ft_handle_redirect_in(cmd, redir) == -1)
				return (-1);
		}
		else if (redir->type == REDIRECT_OUT)
		{
			if (ft_handle_redirect_out(cmd, redir) == -1)
				return (-1);
		}
		else if (redir->type == REDIRECT_APPEND)
		{
			if (ft_handle_redirect_append(cmd, redir) == -1)
				return (-1);
		}
		else if (redir->type == REDIRECT_HEREDOC)
		{
			if (g_data.sig_int == 0)
				ft_handle_heredoc(redir, cmd);
		}
		redir = redir->next;
	}
	return (0);
}

int	ft_open_file(t_command *cmd)
{
	t_redirection	*redir;

	redir = cmd->redirection_list;
	if (open_files_loop(redir, cmd) == -1)
	{
		return (-1);
	}
	return (1);
}
