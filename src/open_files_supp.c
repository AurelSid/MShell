/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_supp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:18:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/12 16:11:35 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_handle_redirect_in(t_command *cmd, t_redirection *redir)
{
	cmd->input_fd = open(redir->filename, O_RDONLY);
	if (cmd->input_fd == -1)
		return (ft_specific_error(redir->filename));
	return (1);
}

int	ft_handle_redirect_out(t_command *cmd, t_redirection *redir)
{
	cmd->output_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->output_fd == -1)
		return (ft_specific_error(redir->filename));
	return (1);
}

int	ft_handle_redirect_append(t_command *cmd, t_redirection *redir)
{
	cmd->output_fd = open(redir->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (cmd->output_fd == -1)
		return (ft_specific_error(redir->filename));
	return (1);
}

void	ft_handle_heredoc(t_redirection *redir, t_command *cmd)
{
	dup2(g_data.original_stdin, STDIN_FILENO);
	ft_limiter_exec(redir, cmd);
}
