/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:30:57 by roko              #+#    #+#             */
/*   Updated: 2024/09/19 13:25:57 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_tokens_list(t_program_data data)
{
	printf("\nToken List\n\n");
	while (data.token_top->next)
	{
		printf("Token content: %s  || Token type: %d\n",
			data.token_top->content, data.token_top->type);
		data.token_top = data.token_top->next;
	}
	printf("Token content: %s  || Token type: %d\n", data.token_top->content,
		data.token_top->type);
}

void	ft_print_commands(t_program_data data)
{
	t_command		*cmd;
	t_redirection	*redir;

	printf("\n---------------------------\n");
	printf("\nCommands List\n\n");
	cmd = data.command_top;
	while (cmd)
	{
		printf("%-15s : %s\n", "Command Name", cmd->name);
		printf("%-15s : %s\n", "Arguments", cmd->args);
		printf("%-15s : %s\n", "Options", cmd->options);
		redir = cmd->redirection_list;
		if (redir)
		{
			printf("%-15s :\n", "Redirections");
			while (redir)
			{
				printf("  - %s\n", redir->filename);
				redir = redir->next;
			}
		}
		else
			printf("%-15s : No redirections\n", "Redirections");
		cmd = cmd->next;
		printf("\n");
	}
}
