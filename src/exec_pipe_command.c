/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/12 16:07:37 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_exec_child_piped_process(t_command *cmd, char **env,
		int pipe_fd[2])
{
	pid_t	process_id;

	process_id = fork();
	if (process_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		if (cmd->name)
		{
			if (ft_check_built_ins(cmd->name) == 1)
				ft_exec_built_ins(cmd);
			else
				execve(cmd->path, ft_args_to_line(cmd), env);
		}
		exit(g_data.exit_status);
	}
}

void	ft_handle_parent_piped_process(int pipe_fd[2],
		pid_t process_id)
{
	int	status;
	int	signal_num;

	status = 0;
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	waitpid(process_id, &status, 0);
	if (WIFEXITED(status))
		g_data.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signal_num = WTERMSIG(status);
	}
	else
		g_data.exit_status = 0;
}

void	ft_exec_piped_command(t_command *cmd, char **env)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		exit(0);
	ft_exec_child_piped_process(cmd, env,pipe_fd);
	ft_handle_parent_piped_process(pipe_fd, getpid());
}
