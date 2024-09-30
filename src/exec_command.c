/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/09/30 13:14:50 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_built_ins(t_command *cmd, t_program_data *data)
{
	if (!ft_strncmp(cmd->name, "env", ft_strlen(cmd->name)))
		ft_print_env(*data);
	else if (!ft_strncmp(cmd->name, "echo", ft_strlen(cmd->name)))
		printf("env detected\n");
	else if (!ft_strncmp(cmd->name, "cd", ft_strlen(cmd->name)))
		printf("env detected\n");
	else if (!ft_strncmp(cmd->name, "pwd", ft_strlen(cmd->name)))
		printf("env detected\n");
	else if (!ft_strncmp(cmd->name, "export", ft_strlen(cmd->name)))
		printf("env detected\n");
	else if (!ft_strncmp(cmd->name, "unset", ft_strlen(cmd->name)))
		printf("env detected\n");
	else if (!ft_strncmp(cmd->name, "exit", ft_strlen(cmd->name)))
		printf("env detected\n");
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

int	ft_exec_cmd(t_command *cmd, char **env)
{
	pid_t	process_id;

	process_id = fork();
	if (process_id == 0)
		execve(cmd->path, ft_args_to_line(cmd), env);
	wait(0);
	return (0);
}

void	ft_exec_pipe(t_command *cmd, char **env)
{
	int		pipe_fd[2];
	pid_t	process_id;

	cmd->input_fd = 0;
	cmd->output_fd = 1;
	if (pipe(pipe_fd) == -1)
		exit(0);
	process_id = fork();
	if (process_id == 0)
	{
		dup2(pipe_fd[1], 1);
		execve(cmd->path, ft_args_to_line(cmd), env);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		// check_stdio_fds();
		close(pipe_fd[0]);
	}
	wait(0);
}
