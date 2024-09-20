/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:25:39 by asideris          #+#    #+#             */
/*   Updated: 2024/09/20 13:43:41 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_try_paths(t_program_data data, char *cmd_name)
{
	char		*cmd_path;
	t_env	*tmp_env;

	tmp_env = data.env;
	while (tmp_env)
	{
		//LEAKS!!!
		cmd_path = ft_strjoin(tmp_env->content, "/");
		cmd_path = ft_strjoin(cmd_path, cmd_name);
		if (access(cmd_path, F_OK) == 0)
			return (1);
		tmp_env = tmp_env->next;
	}
	return (0);
}

void	ft_check_cmd_access(t_program_data *data, char *cmd_name)
{
	printf("\n--------------------------\n");
	if (ft_try_paths(*data, cmd_name) == 0)
	{
		// ft_free_split(cmd_split);
		// ft_error_exit(cmd_name);
		printf("\nCant access command\n");
		// EXIT ERROR//
	}
	else
		printf("\nCommand accessed success\n");
	printf("\n--------------------------\n");
	// ft_free_split(cmd_split);
}

void	ft_check_all_access(t_program_data *data)
{
	t_command *cmd;
	cmd = data->command_top;
	while (cmd)
	{
		ft_check_cmd_access(data, cmd->name);
		cmd = cmd->next;
	}
}