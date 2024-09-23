/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/09/23 13:35:59 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_gnl_to_fd(char **argv, int *pipe_fd)
{
	char	*line;
	char	*limiter;

	close(pipe_fd[0]);
	limiter = argv[2];
	while (1)
	{
		line = readline("");
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
}

void	ft_limiter_exec(char **argv)
{
	int pipe_fd[2];
	pid_t process_id;

	process_id = 0;
	if (pipe(pipe_fd) == -1)
		exit(0);
	process_id = fork();
	if (process_id == -1)
		exit(0);
	else if (process_id == 0)
	{
		ft_gnl_to_fd(argv, pipe_fd);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		wait(NULL);
	}
}