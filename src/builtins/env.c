/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:10:50 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/10 16:04:23 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_command *cmd, t_program_data data)
{
	t_env	*env;
	char	**args;
	int		i;

	env = data.env;
	args = NULL;
	if (cmd->args)
		args = ft_split(cmd->args, ' ');
	i = 0;
	while (args && args[i])
	{
		if (ft_strcmp(args[i], "env"))
		{
			perror("env");
			return ;
		}
		i++;
	}
	while (env)
	{
		if (env->content)
			printf("%s=%s\n", env->var_name, env->content);
		env = env->next;
	}
}
