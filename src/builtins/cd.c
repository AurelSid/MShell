/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:53:08 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/16 17:52:12 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cd(t_command *cmd)
{
	char	*tmp;

	tmp = ft_strtrim(cmd->args, " ");
	if (!tmp || tmp[0] == '~')
		tmp = getenv("HOME");
	if (ft_strcmp(tmp, "-") == 0)
		printf("Shortcuts are not supported\n");
	if (chdir(tmp) == -1)
		printf("cd: %s: Is not a directory\n", cmd->args);
	free(tmp);
}
