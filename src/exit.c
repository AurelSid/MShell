/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:09:46 by asideris          #+#    #+#             */
/*   Updated: 2024/11/13 14:50:28 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_env(void)
{
	t_env	*current_env;
	t_env	*to_free;

	current_env = g_data.env;
	while (current_env)
	{
		to_free = current_env;
		free(to_free->var_name);
		free(to_free->content);
		current_env = current_env->next;
		free(to_free);
	}
	g_data.env = NULL;
}

void	ft_exit_free(char *exit_msg)
{
	printf("%s", exit_msg);
	ft_clean_tokens();
	ft_clean_commands();
}

void	cleanup_and_exit(void)
{
	ft_exit_free("");
	dup2(g_data.original_stdout, STDOUT_FILENO);
	dup2(g_data.original_stdin, STDIN_FILENO);
}
