/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/10/03 16:22:39 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_built_ins(t_command *cmd, t_program_data *data)
{
	if (!ft_strcmp(cmd->name, "env"))
		ft_print_env(*data);
	else if (!ft_strcmp(cmd->name, "echo"))
		ft_echo(cmd->args, cmd->options);
	else if (!ft_strcmp(cmd->name, "cd"))
		printf("env detected\n");
	else if (!ft_strcmp(cmd->name, "pwd"))
		printf("env detected\n");
	else if (!ft_strcmp(cmd->name, "export"))
		printf("env detected\n");
	else if (!ft_strcmp(cmd->name, "unset"))
		printf("env detected\n");
	else if (!ft_strcmp(cmd->name, "exit"))
		printf("env detected\n");
	else
		return (1);
	return (0);
}
char	**ft_args_to_line(t_command *cmd)
{
	char	*tmp_line;
	char	*line;
	char	**line_split;
	int		i;

	i = 0;
	tmp_line = ft_strjoin(cmd->name, " ");
	tmp_line = ft_strjoin(tmp_line, cmd->options);
	tmp_line = ft_strjoin(tmp_line, " ");
	line = ft_strjoin(tmp_line, cmd->args);
	free(tmp_line);
	line_split = ft_split(line, ' ');
	free(line);
	while (line_split[i])
	{
		// printf("Args: [%s]\n", line_split[i]);
		i++;
	}
	return (line_split);
}

void	ft_free_split(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int	ft_exec(t_command *cmd, char **env, t_program_data *data)
{
	int		pipe_fd[2];
	pid_t	process_id;

	if (cmd->next == NULL)
	{
		fprintf(stderr, "executing [%s ]cmd\n", cmd->name);
		process_id = fork();
		if (process_id == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			signal(SIGSTOP, SIG_DFL);
			if (ft_check_built_ins(cmd, data) == 1)
				execve(cmd->path, ft_args_to_line(cmd), env);
		}
		wait(0);
	}
	else
	{
		fprintf(stderr, "executing [%s ]cmd pipe\n", cmd->name);
		if (pipe(pipe_fd) == -1)
			exit(0);
		process_id = fork();
		if (process_id == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			signal(SIGSTOP, SIG_DFL);
			dup2(pipe_fd[1], 1);
			if (ft_check_built_ins(cmd, data) == 0)
				return (0);
			execve(cmd->path, ft_args_to_line(cmd), env);
		}
		else
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], 0);
			close(pipe_fd[0]);
		}
		wait(0);
		return (0);
	}
	return (0);
}
