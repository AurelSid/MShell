/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:53:08 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/01 19:00:21 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cd(t_command *cmd, t_program_data *data)
{
	char	*tmp;
	char	**args;

	args = ft_split_args(cmd->args);
	tmp = args[0];
	if (!data->env && (!tmp || tmp[0] == '~' || ft_strcmp(tmp, "-") == 0))
	{
		write(2, " No env\n", 9);
		data->exit_status = 1;
		return ;
	}
	if (!tmp || tmp[0] == '~')
	{
		tmp = "HOME";
		ft_search_env(&tmp, *data);
	}
	if (ft_strcmp(tmp, "-") == 0)
	{
		tmp = "OLDPWD";
		ft_search_env(&tmp, *data);
	}
	if (chdir(tmp) == -1)
	{
		data->exit_status = 1;
		perror("cd");
	}
	free(tmp);
}
