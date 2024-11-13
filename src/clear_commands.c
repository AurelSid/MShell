/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:34:10 by asideris          #+#    #+#             */
/*   Updated: 2024/11/12 16:00:29 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_commands(void)
{
	t_command	*cmd;
	t_command	*to_free;

	cmd = g_data.command_top;
	while (cmd)
	{
		to_free = cmd;
		cmd = cmd->next;
		free(to_free);
	}
}

void	ft_clean_commands(void)
{
	t_command	*tmp_command;

	tmp_command = g_data.command_top;
	while (tmp_command)
	{
		ft_clean_redirections(tmp_command);
		free(tmp_command->path);
		tmp_command->path = NULL;
		if (tmp_command->name)
			free(tmp_command->name);
		tmp_command->name = NULL;
		free(tmp_command->args);
		tmp_command->args = NULL;
		free(tmp_command->options);
		tmp_command->options = NULL;
		tmp_command = tmp_command->next;
	}
	ft_free_commands();
	g_data.command_top = NULL;
}

void	ft_clean_tokens(void)
{
	t_token	*tmp_token;
	t_token	*to_free;

	tmp_token = g_data.token_top;
	while (tmp_token)
	{
		to_free = tmp_token;
		tmp_token = tmp_token->next;
		free(to_free->content);
		free(to_free);
		to_free = NULL;
	}
	g_data.token_top = NULL;
}

void	ft_clean_redirections(t_command *cmd)
{
	t_redirection	*tmp_red;
	t_redirection	*to_free;

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
