/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/10/31 16:10:37 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_open_file(t_command *cmd, t_program_data *data)
{
	t_redirection	*redir;

	redir = cmd->redirection_list;
	while (redir)
	{
		if (redir->type == REDIRECT_IN)
		{
			cmd->input_fd = open(redir->filename, O_RDONLY);
			if (cmd->input_fd == -1)
				return (ft_specific_error(redir->filename, data));
		}
		else if (redir->type == REDIRECT_OUT)
		{
			cmd->output_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (cmd->output_fd == -1)
				return (ft_specific_error(redir->filename, data));
		}
		else if (redir && redir->type == REDIRECT_APPEND)
		{
			cmd->output_fd = open(redir->filename,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (cmd->output_fd == -1)
				return (ft_specific_error(redir->filename, data));
		}
		else if (redir && redir->type == REDIRECT_HEREDOC)
		{
			dup2(data->original_stdin, STDIN_FILENO);
			ft_limiter_exec(redir, cmd);
		}
		redir = redir->next;
	}
	return (1);
}
