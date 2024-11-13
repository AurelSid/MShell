/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_supp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:16:20 by asideris          #+#    #+#             */
/*   Updated: 2024/11/12 16:05:48 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_built_ins(char *cmd_name)
{
	if (!ft_strcmp(cmd_name, "env") || !ft_strcmp(cmd_name, "echo")
		|| !ft_strcmp(cmd_name, "cd") || !ft_strcmp(cmd_name, "pwd")
		|| !ft_strcmp(cmd_name, "export") || !ft_strcmp(cmd_name, "unset")
		|| !ft_strcmp(cmd_name, "exit"))
		return (1);
	else
		return (0);
}

int	ft_exec_built_ins(t_command *cmd)
{
	if (!ft_strcmp(cmd->name, "env"))
		ft_env(cmd);
	else if (!ft_strcmp(cmd->name, "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd->name, "cd"))
		ft_cd(cmd);
	else if (!ft_strcmp(cmd->name, "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd->name, "export"))
		ft_export(cmd);
	else if (!ft_strcmp(cmd->name, "unset"))
		ft_unset(cmd);
	else if (!ft_strcmp(cmd->name, "exit"))
		ft_exit(cmd);
	else
		return (1);
	return (0);
}
