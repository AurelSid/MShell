/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:16:20 by asideris          #+#    #+#             */
/*   Updated: 2024/10/17 13:50:04 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_set_redir_direction(t_command *cmd)
{
	t_redirection	*redir;

	redir = cmd->redirection_list;
	while (redir)
	{
		if (redir->type == REDIRECT_IN)
			redir->direction = 1;
		else if (redir->type == REDIRECT_HEREDOC)
			redir->direction = 1;
		else if (redir->type == REDIRECT_OUT)
			redir->direction = 2;
		else if (redir->type == REDIRECT_APPEND)
			redir->direction = 2;
		redir = redir->next;
	}
}
int	ft_last_redir(t_redirection *in, t_redirection *out, t_command *cmd)
{
	if (in && in->type == REDIRECT_IN)
		dup2(cmd->input_fd, 0);
	if (out && (out->type == REDIRECT_APPEND || out->type == REDIRECT_OUT))
		dup2(cmd->output_fd, 1);
	return (0);
}
int	ft_open_file(t_command *cmd, t_program_data *data)
{
	t_redirection	*redir;

	(void)data;
	redir = cmd->redirection_list;
	while (redir)
	{
		if (redir && redir->type == REDIRECT_IN)
			cmd->input_fd = open(redir->filename, O_RDONLY);
		if (redir && redir->type == REDIRECT_HEREDOC)
		{
			dup2(data->original_stdin, STDIN_FILENO);
			ft_limiter_exec(redir,cmd);
		}
		if (redir && redir->type == REDIRECT_OUT)
			cmd->output_fd = open(redir->filename, O_WRONLY | O_TRUNC | O_CREAT,
					0644);
		if (redir && redir->type == REDIRECT_APPEND)
			cmd->output_fd = open(redir->filename,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		redir = redir->next;
	}
	return (1);
}

int	ft_apply_redir(t_command *command, t_program_data *data)
{
	t_redirection	*redir;
	t_redirection	*last_in;
	t_redirection	*last_out;

	last_in = NULL;
	last_out = NULL;
	if (command->redirection_list == NULL)
		return (0);
	redir = command->redirection_list;
	ft_set_redir_direction(command);
	while (redir)
	{
		if (redir->direction == 1)
			last_in = redir;
		else
			last_out = redir;
		redir = redir->next;
	}
	if (!ft_open_file(command, data))
		return (1);
	ft_last_redir(last_in, last_out, command);
	return (0);
}
