/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/12 16:08:46 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_fork(pid_t process_id, t_command *cmd, char **env)
{
	if (process_id == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGTSTP, SIG_IGN);
		if (cmd->name)
		{
			if (ft_check_built_ins(cmd->name) == 1)
			{
				ft_exec_built_ins_in_pipe(cmd);
				exit(g_data.exit_status);
			}
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
	p = g_data.pid;
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

void	ft_exit_status(pid_t process_id, int status,
		int signal_num)
{
	waitpid(process_id, &status, 0);
	if (WIFEXITED(status))
		g_data.exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		signal_num = WTERMSIG(status);
	else if (WIFSTOPPED(status))
	{
		signal_num = WSTOPSIG(status);
		if (signal_num == SIGTSTP)
		{
			g_data.exit_status = 146;
		}
	}
	else
		g_data.exit_status = 0;
	ft_handle_child_sig(g_data.exit_status);
}

void	ft_exec_single_command(t_command *cmd, char **env)
{
	pid_t	process_id;
	int		status;
	int		signal_num;

	signal_num = 0;
	status = 0;
	if (ft_check_built_ins(cmd->name) == 1 && g_data.command_top->next == NULL)
	{
		ft_exec_built_ins(cmd);
		return ;
	}
	signal(SIGTSTP, sigtstp_handler);
	process_id = fork();
	g_data.pid = process_id;
	if (ft_fork(process_id, cmd, env))
	{
		ft_exit_status(process_id, status, signal_num);
		ft_handle_child_sig(g_data.exit_status);
	}
}
