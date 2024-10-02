/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:34:10 by asideris          #+#    #+#             */
/*   Updated: 2024/10/01 18:56:18 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_commands(t_program_data *data)
{
	t_command	*cmd;
	t_command	*to_free;

	cmd = data->command_top;
	while (cmd)
	{
		// fprintf(stderr, "freeing\n");
		to_free = cmd;
		cmd = cmd->next;
		free(to_free);
	}
	data->command_top = NULL;
}
void	ft_clean_commands(t_program_data *data)
{
	t_command	*tmp_command;

	tmp_command = data->command_top;
	// fprintf(stderr, "Cleaning commands content\n");
	while (tmp_command)
	{
		// fprintf(stderr, "Cleaning command...\n");
		ft_clean_redirections(tmp_command);
		free(tmp_command->name);
		free(tmp_command->args);
		free(tmp_command->options);
		free(tmp_command->path);
		tmp_command->path = NULL;
		tmp_command = tmp_command->next;
	}
	// fprintf(stderr, "Cleaning commands poiters\n");
	ft_free_commands(data);
}

void	ft_clean_tokens(t_program_data *data)
{
	t_token	*tmp_token;
	t_token	*to_free;

	tmp_token = data->token_top;
	while (tmp_token)
	{
		free(tmp_token->content);
		to_free = tmp_token;
		tmp_token = tmp_token->next;
		free(to_free);
	}
	data->token_top = NULL;
}
void	ft_clean_redirections(t_command *cmd)
{
	t_redirection *tmp_red;
	t_redirection *to_free;

	tmp_red = cmd->redirection_list;
	while (tmp_red)
	{
		free(tmp_red->filename);
		to_free = tmp_red;
		tmp_red = tmp_red->next;
		free(to_free);
	}
	cmd->redirection_list = NULL;
}