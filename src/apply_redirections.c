/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 13:16:20 by asideris          #+#    #+#             */
/*   Updated: 2024/09/19 15:16:50 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_open_file(void)
{
	return (0);
}

int	ft_apply_redir(t_command *command)
{
	int out_fd;
	int in_fd;

	printf("Starting redirections...\n");
	sleep(1);
	in_fd = command->input_fd;
	out_fd = command->output_fd;
	t_redirection *redir;
	redir = command->redirection_list;
	while (redir)
	{
		printf("got redirection type\n");

		redir = redir->next;
	}
	return (0);
}