/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:25:39 by asideris          #+#    #+#             */
/*   Updated: 2024/09/19 16:30:22 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_find_cmd(char **env)
{
	char	*path;
	char	*full_path;
	char	**split_paths;
	int		i;
	int		j;

	j = 0;
	i = 0;
	path = "PATH";
	while (env[i])
	{
		full_path = ft_strnstr(env[i], path, ft_strlen(env[i]));
		if (full_path)
			break ;
		i++;
	}
	full_path = ft_strchr(full_path, '/');
	split_paths = ft_split(full_path, ':');
	while (split_paths[j])
	{
		j++;
	}
	return (split_paths);
}
int	ft_try_paths(char **all_paths, char *cmd_name)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (all_paths[i])
	{
		cmd_path = ft_strjoin(all_paths[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd_name);
		if (access(cmd_path, F_OK) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	ft_check_cmd_access(char **env, char *cmd)
{
	char	**all_paths;
	char	**cmd_split;
	char	*cmd_name;

	cmd_split = ft_split(cmd, ' ');
	cmd_name = cmd_split[0];
	all_paths = ft_find_cmd(env);
	printf("\n--------------------------\n");
	if (ft_try_paths(all_paths, cmd_name) == 0)
	{
		// ft_free_split(cmd_split);
		// ft_error_exit(cmd_name);
		printf("\nCant access command\n");
		//EXIT ERROR//
	}
	else
		printf("\nCommand accessed success\n");
	printf("\n--------------------------\n");
	// ft_free_split(cmd_split);
}

void	ft_check_all_access(t_program_data *data, char **env)
{
	t_command *cmd;
	cmd = data->command_top;
	while (cmd)
	{
		ft_check_cmd_access(env, cmd->name);
		cmd = cmd->next;
	}
}