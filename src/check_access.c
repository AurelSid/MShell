/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/09/25 13:10:39 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_check_all_access(t_program_data *data)
{
	t_env		*env;
	char		*full_path;
	char		**split_paths;
	char		*cmd_path;
	t_command	*cmd;
	int			i;

	cmd = data->command_top;
	i = 0;
	env = data->env;
	while (env)
	{
		if (strcmp(env->var_name, "PATH") == 0)
			full_path = env->content;
		env = env->next;
	}
	split_paths = ft_split(full_path, ':');
	while (cmd)
	{
		i = 0;
		while (split_paths[i])
		{
			cmd_path = ft_strjoin(split_paths[i], "/");
			cmd_path = ft_strjoin(cmd_path, cmd->name);			//THERE SOULD BE LEAKS BUT CANNOT USE STRJOIN FREE
			if (access(cmd_path, F_OK) == 0)
			{
				printf("Command access ok!\n");
				break ;
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}
