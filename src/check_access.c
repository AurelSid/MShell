/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/10/01 19:02:26 by asideris         ###   ########.fr       */
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
	char		*cmd_path;
	t_command	*cmd;
	int			i;
	int			found_working_path;

	found_working_path = 0;
	cmd = data->command_top;
	env = data->env;
	while (env && strcmp(env->var_name, "PATH") != 0)
		env = env->next;
	if (!env)
	{
		printf("PATH environment variable not set\n");
		return (-1);
	}
	full_path = env->content;
	split_paths = ft_split(full_path, ':');
	while (cmd)
	{
		found_working_path = 0;
		i = 0;
		while (split_paths[i])
		{
			cmd_path = ft_strjoin(split_paths[i], "/");
			cmd_path = ft_strjoin(cmd_path, cmd->name);
				// THERE SOULD BE LEAKS BUT CANNOT USE STRJOIN FREE
			if (access(cmd_path, F_OK) == 0)
			{
				ft_set_cmd_path(data, cmd->name, cmd_path);
				found_working_path = 1;
				break ;
			}
			i++;
		}
		if (!found_working_path)
			printf("Access failed\n");
		cmd = cmd->next;
	}
	free(split_paths);
	return (0);
}
