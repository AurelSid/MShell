/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:16:20 by asideris          #+#    #+#             */
/*   Updated: 2024/10/03 15:34:43 by asideris         ###   ########.fr       */
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
int	ft_open_file(t_redirection *in, t_redirection *out, t_command *cmd)
{
	if (in && in->type == REDIRECT_IN)
	{
		cmd->input_fd = open(in->filename, O_RDONLY);
		dup2(cmd->input_fd, 0);
	}
	if (in && in->type == REDIRECT_HEREDOC)
	{
		printf("executing limiter\n");
		ft_limiter_exec(in);
	}
	else if (out && out->type == REDIRECT_OUT)
	{
		cmd->output_fd = open(out->filename, O_WRONLY | O_TRUNC | O_CREAT,
				0644);
		dup2(cmd->output_fd, 1);
	}
	else if (out && out->type == REDIRECT_APPEND)
	{
		cmd->output_fd = open(out->filename, O_WRONLY | O_APPEND | O_CREAT,
				0644);
		dup2(cmd->output_fd, 1);
	}
	if (cmd->input_fd < 0)
		printf("Error opening file");
	if (cmd->input_fd < 0)
		printf("Error opening file");
	return (0);
}

int	ft_apply_redir(t_command *command)
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
	// printf("Last in: %s || Last out: %s\n",
	// 	last_in ? last_in->filename : "None",
	// 	last_out ? last_out->filename : "None");
	ft_open_file(last_in, last_out, command);
	return (0);
}
