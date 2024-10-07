/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:53:08 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/07 13:09:31 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cd(const char *arg)
{
	char	*tmp;

	tmp = ft_strtrim(arg, " ");
	if (!tmp || tmp[0] == '~')
		tmp = getenv("HOME");
	if (ft_strcmp(tmp, "-") == 0)
		printf("Shortcuts are not supported\n");
	if (chdir(tmp) == -1)
		printf("cd: %s: Is not a directory\n", arg);
	free(tmp);
}
