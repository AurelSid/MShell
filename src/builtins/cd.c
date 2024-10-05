/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:53:08 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/05 16:49:05 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_cd(const char *arg)
{
	printf("%s\n", arg);
	if (arg[0] == '~' || ft_strcmp(arg, "-") == 0)
		printf("Shortcuts are not supported\n");
	//if (chdir(arg) == -1)
		printf("output : %d\n", chdir(arg));
}
