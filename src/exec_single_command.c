/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/10/22 17:41:21 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_handle_child_sig(int err)
{
	if (err == 131)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "Quit: 3", 7);
		write(1, "\n", 1);
	}
	if (err == 130)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
	}
}
int	ft_exec_built_ins_in_pipe(t_command *cmd, t_program_data *data)
{
	if (cmd->output_fd != STDOUT_FILENO)
	{
		dup2(cmd->output_fd, STDOUT_FILENO);
		close(cmd->output_fd);
	}
	if (cmd->input_fd != STDIN_FILENO)
	{
		dup2(cmd->input_fd, STDIN_FILENO);
		close(cmd->input_fd);
	}
	return (ft_exec_built_ins(cmd, data));
}
int	ft_fork(pid_t process_id, t_command *cmd, char **env, t_program_data *data)
{
	if (process_id == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGTSTP, SIG_IGN);
		if (cmd->name)
		{
			if (ft_check_built_ins(cmd->name) == 1)
				ft_exec_built_ins_in_pipe(cmd, data);
			else
				execve(cmd->path, ft_args_to_line(cmd), env);
		}
	}
	return (1);
}

void	sigtstp_handler(int signum)
{
	pid_t	p;

	(void)signum;
	p = data.pid;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	write(1, "[1]+  Stopped                 cat", 33);
	write(1, "\n", 1);
	if (p > 0)
	{
		kill(p, SIGKILL);
	}
}

void	ft_exec_single_command(t_command *cmd, char **env, t_program_data *data)
{
	pid_t process_id;
	int status;
	int signal_num;

	if (ft_check_built_ins(cmd->name) == 1)
	{
		ft_exec_built_ins(cmd, data);
		return ;
	}
	signal(SIGTSTP, sigtstp_handler);
	process_id = fork();
	data->pid = process_id;
	if (ft_fork(process_id, cmd, env, data))
	{
		waitpid(process_id, &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			signal_num = WTERMSIG(status);
			data->exit_status = 128 + signal_num;
		}
		else if (WIFSTOPPED(status))
		{
			signal_num = WSTOPSIG(status);
			if (signal_num == SIGTSTP)
			{
				data->exit_status = 146;
			}
		}
		else
			data->exit_status = 1;
		ft_handle_child_sig(data->exit_status);
	}
}