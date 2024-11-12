/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:09:46 by asideris          #+#    #+#             */
/*   Updated: 2024/11/12 15:36:01 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_env(t_program_data *data)
{
	t_env	*current_env;
	t_env	*to_free;

	current_env = data->env;
	while (current_env)
	{
		to_free = current_env;
		free(to_free->var_name);
		free(to_free->content);
		current_env = current_env->next;
		free(to_free);
	}
	data->env = NULL;
}

void	ft_exit_free(t_program_data *data, char *exit_msg)
{
	printf("%s", exit_msg);
	ft_clean_tokens(data);
	ft_clean_commands(data);
}

void	cleanup_and_exit(t_program_data *data)
{
	ft_exit_free(data, "");
	dup2(data->original_stdout, STDOUT_FILENO);
	dup2(data->original_stdin, STDIN_FILENO);
}
