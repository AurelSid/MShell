/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:16:20 by asideris          #+#    #+#             */
/*   Updated: 2024/10/07 13:11:49 by asideris         ###   ########.fr       */
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
			ft_limiter_exec(redir);
		}
		if (redir && redir->type == REDIRECT_OUT)
			cmd->output_fd = open(redir->filename, O_WRONLY | O_TRUNC | O_CREAT,
					0644);
		if (redir && redir->type == REDIRECT_APPEND)
			cmd->output_fd = open(redir->filename,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (cmd->input_fd == -1 && redir->direction == 1
			&& redir->type != REDIRECT_HEREDOC)
		{
			fprintf(stderr, "bash: %s: No such file or directory\n",
				redir->filename);
			ft_exit_free(data, "");
			return (0);
		}
		// fprintf(stderr, "Opened file %s\n", redir->filename);
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
	// if (!last_in && !last_out)
	// {
	// 	fprintf(stderr, "No redirection\n");
	// }
	// else
	// {
	// 	fprintf(stderr, "Last in : %s || Last out : %s\n",
	// 		last_in ? last_in->filename : "None",
	// 		last_out ? last_out->filename : "None");
	// }
	return (0);
}
