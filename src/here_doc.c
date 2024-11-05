/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:24:19 by asideris          #+#    #+#             */
/*   Updated: 2024/11/05 17:31:57 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_gnl_to_fd(int *pipe_fd, t_redirection *in, t_command *cmd)
{
	char	*line;
	char	*limiter;

	(void)cmd;
	limiter = in->filename;
	while (1)
	{
		line = readline(">");
		if (line == NULL)
			break ;
		if (ft_strlen(limiter) == 0 && line[0] == '\n')
			return (free(line), exit(0));
		if (ft_strlen(limiter) > 0 && ft_strncmp(line, limiter,
				ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}

void	ft_here_sig(int err)
{
	(void)err;
	write(1, "\n", 1);
	rl_on_new_line();
	exit(0);
}

void	ft_limiter_exec(t_redirection *in, t_command *cmd)
{
	int		pipe_fd[2];
	pid_t	process_id;
	int		status;

	if (pipe(pipe_fd) == -1)
		exit(1);
	process_id = fork();
	if (process_id == -1)
		exit(1);
	else if (process_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		ft_gnl_to_fd(pipe_fd, in, cmd);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		waitpid(process_id, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			g_data.sig_int = 1;
		else
			g_data.sig_int = 0;
	}
}
