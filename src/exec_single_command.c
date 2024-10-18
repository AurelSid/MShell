/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/10/18 12:55:31 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_fork(pid_t process_id, t_command *cmd, char **env)
{
	if (process_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (cmd->name)
			execve(cmd->path, ft_args_to_line(cmd), env);
		return (0);
	}
	return (1);
}

void	ft_exec_single_command(t_command *cmd, char **env, t_program_data *data)
{
	pid_t	process_id;
	int		status;
	int		signal_num;

	if (ft_check_built_ins(cmd) == 0)
		ft_exec_built_ins(cmd, data);
	else
	{
		process_id = fork();
		ft_fork(process_id, cmd, env);
		waitpid(process_id, &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			signal_num = WTERMSIG(status);
			data->exit_status = 128 + signal_num;
		}
		else
			data->exit_status = 1;
	}
}
