/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:30:57 by roko              #+#    #+#             */
/*   Updated: 2024/09/26 12:44:31 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_tokens_list(t_program_data data)
{
	t_token	*current;
	int		frame_width;

	current = data.token_top;
	frame_width = 50;
	printf("\n");
	printf("+");
	for (int i = 0; i < frame_width - 2; i++)
		printf("-");
	printf("+\n");
	printf("| %-46s |\n", "Token List");
	printf("|");
	for (int i = 0; i < frame_width - 2; i++)
		printf("-");
	printf("|\n");
	while (current)
	{
		printf("| Token content: %-30s || Type: %-2d |\n", current->content,
			current->type);
		current = current->next;
	}
	printf("+");
	for (int i = 0; i < frame_width - 2; i++)
		printf("-");
	printf("+\n");
}

void	ft_print_commands(t_program_data data)
{
	t_command		*cmd;
	t_redirection	*redir;
	int				frame_width;

	frame_width = 50;
	printf("\n");
	printf("+");
	for (int i = 0; i < frame_width - 2; i++)
		printf("-");
	printf("+\n");
	printf("| %-46s |\n", "Commands List");
	printf("|");
	for (int i = 0; i < frame_width - 2; i++)
		printf("-");
	printf("|\n");
	cmd = data.command_top;
	while (cmd)
	{
		printf("| %-15s : %-30s |\n", "Command Name", cmd->name);
		printf("| %-15s : %-30s |\n", "Arguments", cmd->args);
		printf("| %-15s : %-30s |\n", "Options", cmd->options);
		printf("| %-15s : %-30s |\n", "Path", cmd->path);
		redir = cmd->redirection_list;
		if (redir)
		{
			printf("| %-15s : \n", "Redirections");
			while (redir)
			{
				printf("| 	name: %-10s  tyoe:%-3d file:%-3s\n |",
						redir->filename, redir->type, redir->filename);
				redir = redir->next;
			}
		}
		else
			printf("| %-15s : %-30s |\n", "Redirections", "No redirections");
		cmd = cmd->next;
		printf("|");
		for (int i = 0; i < frame_width - 2; i++)
			printf("-");
		printf("|\n");
	}
	printf("+");
	for (int i = 0; i < frame_width - 2; i++)
		printf("-");
	printf("+\n");
}

void	ft_print_env(t_program_data data)
{
	t_env	*env;

	printf("\n------------------------------\n");
	printf("\n   Env copy list\n");
	env = data.env;
	while (env)
	{
		printf("%-30s : %s\n", env->var_name, env->content);
		env = env->next;
	}
}
