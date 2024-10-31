/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/10/31 15:03:10 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_access(t_program_data *data, char *cmd_path_2, t_command *cmd,
		int *found_working_path)
{
	if (access(cmd_path_2, F_OK) == 0)
	{
		*found_working_path = 1;
		if (access(cmd_path_2, X_OK) == -1)
		{
			*found_working_path = 2;
			ft_set_cmd_path(data, cmd->name, cmd_path_2);
			fprintf(stderr, "bash: %s: Permission denied\n", cmd->name);
			data->exit_status = 2;
			return (1);
		}
		ft_set_cmd_path(data, cmd->name, cmd_path_2);
	}
	return (0);
}

int	ft_while_split_util(t_command *cmd, char **split_paths, char *cmd_path_1,
		char **cmd_path_2)
{
	if (cmd->name)
	{
		*cmd_path_2 = ft_strjoin(cmd_path_1, cmd->name);
		free(cmd_path_1);
		if (!*cmd_path_2)
		{
			ft_free_split(split_paths);
			return (1);
		}
	}
	else
	{
		free(cmd_path_1);
		*cmd_path_2 = ft_strdup("/bin/true");
		if (!cmd_path_2)
		{
			ft_free_split(split_paths);
			return (1);
		}
	}
	return (0);
}

int	ft_while_split(char **split_paths, t_command *cmd, int *found_working_path,
		t_program_data *data)
{
	char	*cmd_path_1;
	char	*cmd_path_2;
	int		i;

	cmd_path_2 = NULL;
	i = 0;
	while (split_paths[i])
	{
		cmd_path_1 = ft_strjoin(split_paths[i], "/");
		if (!cmd_path_1)
		{
			ft_free_split(split_paths);
			return (1);
		}
		if (ft_while_split_util(cmd, split_paths, cmd_path_1, &cmd_path_2))
			return (1);
		ft_check_access(data, cmd_path_2, cmd, found_working_path);
		if (*found_working_path == 1)
			break ;
		else if (*found_working_path == 2)
			return (1);
		free(cmd_path_2);
		i++;
	}
	return (0);
}

int	ft_while_cmd(t_command *cmd, char **split_paths, t_program_data *data)
{
	int	found_working_path;
	int	i;

	found_working_path = 0;
	while (cmd)
	{
		found_working_path = 0;
		i = 0;
		if (!ft_check_absolute_p(cmd, data))
		{
			cmd = cmd->next;
			continue ;
		}
		if (ft_while_split(split_paths, cmd, &found_working_path, data))
			return (1);
		if (cmd->name && !found_working_path
			&& ft_check_built_ins(cmd->name) == 0)
		{
			fprintf(stderr, "bash: %s: command not found\n", cmd->name);
			data->exit_status = 127;
			ft_free_split(split_paths);
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}

int	ft_check_all_access(t_program_data *data)
{
	t_env		*env;
	char		*full_path;
	char		**split_paths;
	t_command	*cmd;

	cmd = data->command_top;
	env = data->env;
	while (cmd)
	{
		if (cmd->name && ft_check_built_ins(cmd->name))
		{
			cmd = cmd->next;
			continue ;
		}
		while (env && strcmp(env->var_name, "PATH") != 0)
			env = env->next;
		if (!env)
			return (-1);
		full_path = env->content;
		split_paths = ft_split(full_path, ':');
		if (!split_paths)
			return (-1);
		if (ft_while_cmd(cmd, split_paths, data))
			return (1);
		if (split_paths)
			ft_free_split(split_paths);
		cmd = cmd->next;
	}
	return (0);
}
