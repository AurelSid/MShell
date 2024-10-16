/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/10/16 16:54:05 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_built_ins(t_command *cmd)
{
	if (ft_strcmp(cmd->name, "env") && ft_strcmp(cmd->name, "echo")
		&& ft_strcmp(cmd->name, "cd") && ft_strcmp(cmd->name, "pwd")
		&& ft_strcmp(cmd->name, "export") && ft_strcmp(cmd->name, "unset")
		&& ft_strcmp(cmd->name, "exit"))
		return (1);
	else
		return (0);
}
int	ft_exec_built_ins(t_command *cmd, t_program_data *data)
{
	if (!ft_strcmp(cmd->name, "env"))
		ft_env(*data);
	else if (!ft_strcmp(cmd->name, "echo"))
		ft_echo(cmd->args, cmd->options, *data);
	else if (!ft_strcmp(cmd->name, "cd"))
		ft_cd(cmd->args);
	else if (!ft_strcmp(cmd->name, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd->name, "export"))
		ft_export(cmd->args, data);
	else if (!ft_strcmp(cmd->name, "unset"))
		ft_unset(cmd->args, data);
	else if (!ft_strcmp(cmd->name, "exit"))
		ft_exit(cmd->args);
	else
		return (1);
	return (0);
}
char	**ft_args_to_line(t_command *cmd)
{
	char	*tmp_line_1;
	char	*tmp_line_2;
	char	*tmp_line_3;
	char	*line;
	char	**line_split;
	int		i;

	i = 0;
	tmp_line_1 = ft_strjoin(cmd->name, " ");
	tmp_line_2 = ft_strjoin(tmp_line_1, cmd->options);
	free(tmp_line_1);
	tmp_line_3 = ft_strjoin(tmp_line_2, " ");
	free(tmp_line_3);
	line = ft_strjoin(tmp_line_2, cmd->args);
	free(tmp_line_2);
	line_split = ft_split(line, ' ');
	free(line);
	while (line_split[i])
		i++;
	return (line_split);
}

void	ft_setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
		if (process_id == 0)
		{
			ft_setup_child_signals();
			if (cmd->name)
				execve(cmd->path, ft_args_to_line(cmd), env);
		}
		else
		{
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
}

void	ft_exec_piped_command(t_command *cmd, char **env, t_program_data *data)
{
	int		pipe_fd[2];
	pid_t	process_id;
	int		status;
	int		signal_num;

	if (pipe(pipe_fd) == -1)
		exit(0);
	process_id = fork();
	if (process_id == 0)
	{
		ft_setup_child_signals();
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		if (ft_exec_built_ins(cmd, data) == 1 && cmd->name)
			execve(cmd->path, ft_args_to_line(cmd), env);
		exit(data->exit_status);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		waitpid(process_id, &status, 0);
		data->exit_status = 0;
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
char	**ft_env_to_tab(t_program_data *data)
{
	t_env	*tmp_env;
	int		env_nmbr;
	char	**tab;
	int		i;
	char	*tmp;

	i = 0;
	env_nmbr = 0;
	tmp_env = data->env;
	while (tmp_env)
	{
		env_nmbr++;
		tmp_env = tmp_env->next;
	}
	tab = malloc(sizeof(char *) * (env_nmbr + 1));
	tab[env_nmbr] = NULL;
	tmp_env = data->env;
	while (tmp_env)
	{
		tmp = ft_strjoin(tmp_env->var_name, "=");
		tab[i] = ft_strjoin(tmp, tmp_env->content);
		free(tmp);
		tmp_env = tmp_env->next;
		i++;
	}
	return (tab);
}
int	ft_exec(t_command *cmd, char **env, t_program_data *data)
{
	char	**tab;

	(void)env;
	tab = ft_env_to_tab(data);
	signal(SIGINT, SIG_IGN);
	if (cmd->next == NULL)
		ft_exec_single_command(cmd, tab, data);
	else
		ft_exec_piped_command(cmd, tab, data);
	ft_free_split(tab);
	signal(SIGINT, ft_handle_signals);
	return (0);
}
