/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/05 17:49:15 by asideris         ###   ########.fr       */
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
			printf("bash: %s: Permission denied\n", cmd->name);
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

void	ft_while_cmd_supp(t_command *cmd, t_program_data *data,
		char **split_paths)
{
	write(2, "bash: ", 6);
	write(2, cmd->name, ft_strlen(cmd->name));
	write(2, ": command not found\n", 20);
	data->exit_status = 127;
	ft_free_split(split_paths);
}
