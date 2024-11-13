/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:46:32 by asideris          #+#    #+#             */
/*   Updated: 2024/11/13 17:20:25 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_set_cmd_path(char *cmd_name, char *path)
{
	t_command	*cmd;

	cmd = g_data.command_top;
	while (cmd)
	{
		if (cmd->name == cmd_name)
		{
			free(cmd->path);
			cmd->path = path;
			return (0);
		}
		cmd = cmd->next;
	}
	return (0);
}

int	ft_check_absolute_p(t_command *cmd)
{
	if (cmd->name && access(cmd->name, F_OK) == 0 && access(cmd->name,
			X_OK) == 0)
	{
		ft_set_cmd_path(cmd->name, ft_strdup(cmd->name));
		return (0);
	}
	return (1);
}

int	ft_while_cmd(t_command *cmd, char **split_paths)
{
	int	found_working_path;
	int	i;

	found_working_path = 0;
	while (cmd)
	{
		found_working_path = 0;
		i = 0;
		if (!ft_check_absolute_p(cmd))
		{
			cmd = cmd->next;
			continue ;
		}
		if (ft_while_split(split_paths, cmd, &found_working_path))
			return (1);
		if (cmd->name && !found_working_path
			&& ft_check_built_ins(cmd->name) == 0)
		{
			ft_while_cmd_supp(cmd, split_paths);
			return (1);
		}
		cmd = cmd->next;
	}
	return (0);
}

int	ft_supp(t_env *env, char **full_path, char ***split_paths)
{
	t_env	*env_tmp;

	env_tmp = env;
	while (env_tmp && strcmp(env_tmp->var_name, "PATH") != 0)
		env_tmp = env_tmp->next;
	if (!env_tmp)
		return (-1);
	*full_path = env_tmp->content;
	*split_paths = ft_split(*full_path, ':');
	if (!*split_paths)
		return (-1);
	return (0);
}

int	ft_check_all_access(void)
{
	static char	*full_path;
	char		**split_paths;
	t_command	*cmd;

	split_paths = NULL;
	cmd = g_data.command_top;
	while (cmd)
	{
		if (ft_check_absolute_p(cmd))
		{
			if (cmd->name && ft_check_built_ins(cmd->name))
			{
				cmd = cmd->next;
				continue ;
			}
			if (ft_supp(g_data.env, &full_path, &split_paths) == -1)
				return (-1);
			if (ft_while_cmd(cmd, split_paths))
				return (1);
			if (split_paths)
				ft_free_split(split_paths);
		}
		cmd = cmd->next;
	}
	return (0);
}
