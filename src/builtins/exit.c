/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:17:09 by vpelc             #+#    #+#             */
/*   Updated: 2024/11/12 16:15:28 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_split_count(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

void	ft_exit(t_command *cmd)
{
	int		code;
	char	**args;

	args = ft_split_args(cmd->args);
	if ((ft_split_count(args)) > 1)
	{
		write(2, " too many arguments\n", 20);
		exit(1);
	}
	if (g_data.command_top->next == NULL && g_data.child == 0)
		printf("exit\n");
	if (cmd->args[0])
		code = ft_atol(args[0]);
	else
		code = 0;
	if (code > 255)
		code = (unsigned char)code;
	exit(code);
}
