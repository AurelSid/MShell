/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:10:50 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/01 13:16:40 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(t_program_data data)
{
	t_env	*env;

	env = data.env;
	while (env)
	{
		printf("%s=%s\n", env->var_name, env->content);
		env = env->next;
	}
}
