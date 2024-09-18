/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:30:57 by roko              #+#    #+#             */
/*   Updated: 2024/09/18 17:56:54 by asideris         ###   ########.fr       */
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
		printf("Command Name: %s\n", cmd->name);
		redir = cmd->redirection_list;
		if (redir)
		{
			printf("Redirections:\n");
			while (redir)
			{
				printf("  - %s\n", redir->filename);
				redir = redir->next;
			}
		}
		else
			printf("No redirections\n");
		cmd = cmd->next;
		printf("\n");
	}

}
