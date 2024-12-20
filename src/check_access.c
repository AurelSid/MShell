/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/14 13:27:19 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_access(char *cmd_path_2, t_command *cmd, int *found_working_path)
{
	if (access(cmd_path_2, F_OK) == 0)
	{
		*found_working_path = 1;
		if (access(cmd_path_2, X_OK) == -1)
		{
			*found_working_path = 2;
			ft_set_cmd_path(cmd->name, cmd_path_2);
			printf("bash: %s: Permission denied\n", cmd->name);
			ft_return_data()->exit_status = 2;
			return (1);
		}
		ft_set_cmd_path(cmd->name, cmd_path_2);
	}
	return (0);
}

int	ft_while_split_util(t_command *cmd, char **split_paths, char **cmd_path_1,
		char **cmd_path_2)
{
	if (cmd->name)
	{
		*cmd_path_2 = ft_strjoin(*cmd_path_1, cmd->name);
		free(*cmd_path_1);
		if (!*cmd_path_2)
		{
			ft_free_split(split_paths);
			return (1);
		}
	}
	else
	{
		free(*cmd_path_1);
		*cmd_path_2 = ft_strdup("/bin/true");
		if (!*cmd_path_2)
		{
			ft_free_split(split_paths);
			return (1);
		}
	}
	return (0);
}

int	ft_while_split(char **split_paths, t_command *cmd, int *found_working_path)
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
		if (ft_while_split_util(cmd, split_paths, &cmd_path_1, &cmd_path_2))
			return (1);
		ft_check_access(cmd_path_2, cmd, found_working_path);
		if (*found_working_path == 1)
			return (0);
		else if (*found_working_path == 2)
			return (free(cmd_path_2), 1);
		free(cmd_path_2);
		i++;
	}
	return (0);
}

void	ft_while_cmd_supp(t_command *cmd, char **split_paths)
{
	write(2, "bash: ", 6);
	write(2, cmd->name, ft_strlen(cmd->name));
	write(2, ": command not found\n", 20);
	ft_return_data()->exit_status = 127;
	ft_free_split(split_paths);
}
