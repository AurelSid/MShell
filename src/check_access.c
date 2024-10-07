/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/10/07 18:45:28 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_set_cmd_path(t_program_data *data, char *cmd_name, char *path)
{
	t_command	*cmd;

	cmd = data->command_top;
	while (cmd)
	{
		if (cmd->name == cmd_name)
		{
			cmd->path = path;
			return (0);
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
	char		*cmd_path_1;
	char		*cmd_path_2;
	t_command	*cmd;
	int			i;
	int			found_working_path;

	found_working_path = 0;
	cmd = data->command_top;
	env = data->env;
	if (cmd->name && !ft_check_built_ins(cmd))
		return (0);
	while (env && strcmp(env->var_name, "PATH") != 0)
		env = env->next;
	if (!env)
	{
		printf("PATH environment variable not set\n");
		return (-1);
	}
	full_path = env->content;
	split_paths = ft_split(full_path, ':');
	if (!split_paths)
		return (-1);
	while (cmd)
	{
		found_working_path = 0;
		i = 0;
		while (split_paths[i])
		{
			cmd_path_1 = ft_strjoin(split_paths[i], "/");
			if (!cmd_path_1)
			{
				ft_free_split(split_paths);
				return (-1);
			}
			if (cmd->name)
			{
				cmd_path_2 = ft_strjoin(cmd_path_1, cmd->name);
				free(cmd_path_1);
				if (!cmd_path_2)
				{
					ft_free_split(split_paths);
					return (-1);
				}
			}
			else
			{
				free(cmd_path_1);
				cmd_path_2 = ft_strdup("/bin/true");
				if (!cmd_path_2)
				{
					ft_free_split(split_paths);
					return (-1);
				}
			}
			if (access(cmd_path_2, F_OK) == 0)
			{
				ft_set_cmd_path(data, cmd->name, cmd_path_2);
				found_working_path = 1;
				break ;
			}
			free(cmd_path_2);
			i++;
		}
		if (cmd->name && !found_working_path && ft_check_built_ins(cmd) == 1)
		{
			fprintf(stderr, "bash: %s: command not found\n", cmd->name);
			ft_free_split(split_paths);
			return (1);
		}
		cmd = cmd->next;
	}
	ft_free_split(split_paths);
	return (0);
}
