/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_supp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:18:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/01 19:04:02 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_handle_redirect_in(t_command *cmd, t_redirection *redir,
		t_program_data *data)
{
	cmd->input_fd = open(redir->filename, O_RDONLY);
	if (cmd->input_fd == -1)
		return (ft_specific_error(redir->filename, data));
	return (1);
}

int	ft_handle_redirect_out(t_command *cmd, t_redirection *redir,
		t_program_data *data)
{
	cmd->output_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->output_fd == -1)
		return (ft_specific_error(redir->filename, data));
	return (1);
}

int	ft_handle_redirect_append(t_command *cmd, t_redirection *redir,
		t_program_data *data)
{
	cmd->output_fd = open(redir->filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (cmd->output_fd == -1)
		return (ft_specific_error(redir->filename, data));
	return (1);
}

void	ft_handle_heredoc(t_redirection *redir, t_command *cmd,
		t_program_data *data)
{
	dup2(data->original_stdin, STDIN_FILENO);
	ft_limiter_exec(redir, cmd);
}
