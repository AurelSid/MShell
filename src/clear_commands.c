/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:34:10 by asideris          #+#    #+#             */
/*   Updated: 2024/11/14 13:27:19 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_commands(void)
{
	t_command	*cmd;
	t_command	*to_free;

	cmd = ft_return_data()->command_top;
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
	t_command	*to_free;

	tmp_command = ft_return_data()->command_top;
	while (tmp_command)
	{
		to_free = tmp_command;
		tmp_command = tmp_command->next;
		ft_clean_redirections(to_free);
		free(to_free->path);
		to_free->path = NULL;
		free(to_free->name);
		to_free->name = NULL;
		free(to_free->args);
		to_free->args = NULL;
		free(to_free->options);
		to_free->options = NULL;
		free(to_free);
		to_free = NULL;
	}
	ft_return_data()->command_top = NULL;
}

void	ft_clean_tokens(void)
{
	t_token	*tmp_token;
	t_token	*to_free;

	tmp_token = ft_return_data()->token_top;
	while (tmp_token)
	{
		to_free = tmp_token;
		tmp_token = tmp_token->prev;
		free(to_free->content);
		free(to_free);
		to_free = NULL;
	}
	ft_return_data()->token_top = NULL;
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
