/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:37:09 by asideris          #+#    #+#             */
/*   Updated: 2024/09/26 17:42:29 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_gnl_to_fd(int *pipe_fd, t_redirection *in)
{
	char	*line;
	char	*limiter;

	limiter = in->filename;
	while (1)
	{
		line = readline("Here_doc->");
		if (line == NULL)
			break ;
		if (ft_strlen(limiter) == 0 && line[0] == '\n')
			return (free(line), exit(0));
		if (ft_strlen(limiter) > 0 && ft_strncmp(line, limiter,
				ft_strlen(limiter)) == 0)
		{
			free(line);
			exit(0);
		}
	
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[0]);
}

void	ft_limiter_exec(t_redirection *in)
{
	int pipe_fd[2];
	pid_t process_id;

	process_id = 0;
	if (pipe(pipe_fd) == -1)
		exit(0);
	process_id = fork();
	printf("PID:%d\n", process_id);
	if (process_id == -1)
		exit(0);
	else if (process_id == 0)
	{
		ft_gnl_to_fd(pipe_fd, in);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		wait(0);
	}
}