/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:18:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/10 17:22:04 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ft_commands_fill_list_r(t_program_data *data, t_token *tmp,
		char **args, char **opt)
{
	t_command		*cmd;
	t_redirection	*redir;
	char			*cmd_n;
	char			*free_tmp;

	redir = NULL;
	while (tmp && ((tmp->type == REDIRECT_IN || tmp->type == REDIRECT_APPEND
				|| tmp->type == REDIRECT_HEREDOC || tmp->type == REDIRECT_OUT)
			&& (tmp->next->type == WORD || tmp->next->type == DOUBLE_QUOTE
				|| tmp->next->type == SINGLE_QUOTE)))
	{
		redir = ft_new_redirection(tmp->next->content, redir, tmp->type);
		tmp = tmp->next->next;
	}
	if (!tmp || tmp->type == PIPE)
		cmd_n = NULL;
	else
	{
		if (tmp->type == WORD)
			cmd_n = tmp->content;
		tmp = tmp->next;
		while (tmp && (tmp->content[0] == '-' && (tmp->type == WORD
					|| tmp->type == SINGLE_QUOTE || tmp->type == DOUBLE_QUOTE)))
		{
			free_tmp = *opt;
			*opt = ft_strjoin(free_tmp, tmp->content);
			free(free_tmp);
			tmp = tmp->next;
			free_tmp = *opt;
			*opt = ft_strjoin(free_tmp, " ");
			free(free_tmp);
		}
		while (tmp && (tmp->type == WORD || tmp->type == SINGLE_QUOTE
				|| tmp->type == DOUBLE_QUOTE))
		{
			free_tmp = *args;
			*args = ft_strjoin(free_tmp, tmp->content);
			free(free_tmp);
			tmp = tmp->next;
			free_tmp = *args;
			*args = ft_strjoin(free_tmp, " ");
			free(free_tmp);
		}
	}
	cmd = ft_new_command(cmd_n, data, *args, *opt);
	while ((tmp && tmp->next) && tmp->type != PIPE)
	{
		if ((tmp->type == REDIRECT_IN || tmp->type == REDIRECT_OUT
				|| tmp->type == REDIRECT_HEREDOC
				|| tmp->type == REDIRECT_APPEND) && (tmp->next->type == WORD
				|| tmp->next->type == SINGLE_QUOTE
				|| tmp->next->type == DOUBLE_QUOTE))
			redir = ft_new_redirection(tmp->next->content, redir, tmp->type);
		else
			printf("ERROR\n");
		tmp = tmp->next->next;
	}
	cmd->redirection_list = redir;
	return (tmp);
}

void	ft_commands_fill_list(t_program_data *data)
{
	t_token	*tmp;
	char	*opt;
	char	*args;

	opt = ft_calloc(1, 1);
	if (!opt)
		return ;
	args = ft_calloc(1, 1);
	if (!args)
		return ;
	tmp = data->token_top;
	tmp = ft_commands_fill_list_r(data, tmp, &args, &opt);
	if ((tmp && tmp->next) && tmp->type == PIPE)
	{
		tmp = tmp->next;
		data->token_top = tmp;
		ft_commands_fill_list(data);
	}
	if (opt)
		free(opt);
	if (args)
		free(args);
}
