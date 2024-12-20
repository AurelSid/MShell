/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/18 19:26:36 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_last_redir(t_redirection *in, t_redirection *out, t_command *cmd)
{
	if (in && in->type == REDIRECT_IN)
		dup2(cmd->input_fd, STDIN_FILENO);
	if (out && (out->type == REDIRECT_APPEND || out->type == REDIRECT_OUT))
		dup2(cmd->output_fd, STDOUT_FILENO);
	else
		dup2(ft_return_data()->original_stdout, STDOUT_FILENO);
	return (0);
}

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

int	ft_specific_error(const char *filename)
{
	(void)filename;
	if (errno == EACCES)
	{
		write(2, " Permission denied\n", 19);
	}
	else if (errno == ENOENT)
		write(2, " No such file or directory\n", 27);
	else if (errno == EISDIR)
		write(2, " Is a directory\n", 15);
	else if (errno == ENOSPC)
		write(2, " No space left on device\n", 24);
	else if (errno == EROFS)
		write(2, " Read-only file system\n", 22);
	ft_return_data()->exit_status = 1;
	return (-1);
}

int	ft_apply_redir(t_command *command)
{
	t_redirection	*redir;

	command->last_in = NULL;
	command->last_out = NULL;
	if (command->redirection_list == NULL)
		return (0);
	redir = command->redirection_list;
	ft_set_redir_direction(command);
	while (redir)
	{
		if (redir->direction == 1)
			command->last_in = redir;
		else
			command->last_out = redir;
		redir = redir->next;
	}
	if (ft_open_file(command) == -1)
	{
		command->output_fd = -1;
		command->input_fd = -1;
		ft_return_data()->exit_status = 1;
		return (1);
	}
	return (0);
}
