/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:16:20 by asideris          #+#    #+#             */
/*   Updated: 2024/09/25 17:13:52 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_set_redir_type(t_command *cmd)
{
	t_redirection	*redir;

	redir = cmd->redirection_list;
	while (redir)
	{
		if (redir->type == REDIRECT_IN)
			redir->direction = 1;
		else if (redir->direction == REDIRECT_HEREDOC)
			redir->direction = 1;
		else if (redir->direction == REDIRECT_OUT)
			redir->direction = 2;
		else if (redir->direction == REDIRECT_APPEND)
			redir->direction = 2;
		redir = redir->next;
	}
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
	ft_set_redir_type(command);
	printf("Starting redirections...\n");
	while (redir)
	{
		if (redir->direction == 1)
			last_in = redir;
		else
			last_out = redir;
		redir = redir->next;
	}
	
	printf("Last in: %s || Last out: %s\n",
		last_in ? last_in->filename : "None",
		last_out ? last_out->filename : "None");
	return (0);
}
