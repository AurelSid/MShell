/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:46:32 by asideris          #+#    #+#             */
/*   Updated: 2024/10/16 13:49:08 by asideris         ###   ########.fr       */
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
