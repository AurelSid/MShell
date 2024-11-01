/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:46:32 by asideris          #+#    #+#             */
/*   Updated: 2024/11/01 18:38:34 by asideris         ###   ########.fr       */
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

int	ft_check_absolute_p(t_command *cmd, t_program_data *data)
{
	if (cmd->name && access(cmd->name, F_OK) == 0 && access(cmd->name,
			X_OK) == 0)
	{
		ft_set_cmd_path(data, cmd->name, ft_strdup(cmd->name));
		return (0);
	}
	return (1);
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
			ft_while_cmd_supp(cmd, data, split_paths);
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}

int	ft_supp(t_env *env, char **full_path, char ***split_paths)
{
	while (env && strcmp(env->var_name, "PATH") != 0)
		env = env->next;
	if (!env)
		return (-1);
	*full_path = env->content;
	*split_paths = ft_split(*full_path, ':');
	if (!*split_paths)
		return (-1);
	return (0);
}

int	ft_check_all_access(t_program_data *data)
{
	t_env		*env;
	char		*full_path;
	char		**split_paths;
	t_command	*cmd;

	full_path = NULL;
	split_paths = NULL;
	cmd = data->command_top;
	env = data->env;
	while (cmd)
	{
		if (cmd->name && ft_check_built_ins(cmd->name))
		{
			cmd = cmd->next;
			continue ;
		}
		if (ft_supp(env, &full_path, &split_paths) == -1)
			return (-1);
		if (ft_while_cmd(cmd, split_paths, data))
			return (1);
		if (split_paths)
			ft_free_split(split_paths);
		cmd = cmd->next;
	}
	return (0);
}
