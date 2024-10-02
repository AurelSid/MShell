/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:18:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/10/02 15:29:02 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
		/!\ LEAKS ON STRJOIN /!\
*/

void	ft_commands_fill_list_c(t_program_data *data, t_token *tmp)
{
	t_command	*cmd;
	char		*opt;
	char		*args;

	opt = ft_calloc(1, 1);
	if (!opt)
		return ;
	args = ft_calloc(1, 1);
	if (!args)
		return ;
	tmp = tmp->next;
	while (tmp && (tmp->content[0] == '-' && (tmp->type == WORD
				|| tmp->type == SINGLE_QUOTE || tmp->type == DOUBLE_QUOTE)))
	{
		opt = ft_strjoin(opt, tmp->content);
		tmp = tmp->next;
		opt = ft_strjoin(opt, " ");
	}
	while (tmp && (tmp->type == WORD || tmp->type == SINGLE_QUOTE
			|| tmp->type == DOUBLE_QUOTE))
	{
		args = ft_strjoin(args, tmp->content);
		tmp = tmp->next;
		args = ft_strjoin(args, " ");
	}
	cmd = ft_new_command(data->token_top->content, data, args, opt);
	while ((tmp && tmp->next) && tmp->type != PIPE)
	{
		if ((tmp->type == REDIRECT_IN || tmp->type == REDIRECT_OUT
				|| tmp->type == REDIRECT_HEREDOC
				|| tmp->type == REDIRECT_APPEND) && tmp->next->type == WORD)
			ft_new_redirection(tmp->next->content, cmd, tmp->type);
		else
			printf("ERROR\n");
		tmp = tmp->next->next;
	}
}

void	ft_commands_fill_list_r(t_program_data *data, t_token *tmp)
{
	t_command	*cmd;
	t_type		r_type;
	char		*opt;
	char		*args;
	char		*r_arg;
	char		*cmd_n;

	r_type = tmp->type;
	tmp = tmp->next;
	opt = ft_calloc(1, 1);
	if (!opt)
		return ;
	args = ft_calloc(1, 1);
	if (!args)
		return ;
	if (tmp && (tmp->type == WORD))
		r_arg = tmp->content;
	tmp = tmp->next;
	if (tmp && (tmp->type == WORD))
		cmd_n = tmp->content;
	tmp = tmp->next;
	while (tmp && (tmp->type == 1 && tmp->content[0] == '-'))
	{
		opt = ft_strjoin(opt, tmp->content);
		tmp = tmp->next;
		opt = ft_strjoin(opt, " ");
	}
	while (tmp && (tmp->type == WORD || tmp->type == SINGLE_QUOTE
			|| tmp->type == DOUBLE_QUOTE))
	{
		args = ft_strjoin(args, tmp->content);
		tmp = tmp->next;
		args = ft_strjoin(args, " ");
	}
	cmd = ft_new_command(cmd_n, data, args, opt);
	ft_new_redirection(r_arg, cmd, r_type);
	while ((tmp && tmp->next) && tmp->type != PIPE)
	{
		if ((tmp->type == REDIRECT_IN || tmp->type == REDIRECT_OUT
				|| tmp->type == REDIRECT_HEREDOC
				|| tmp->type == REDIRECT_APPEND) && tmp->next->type == WORD)
			ft_new_redirection(tmp->next->content, cmd, tmp->type);
		else
			printf("ERROR\n");
		tmp = tmp->next->next;
	}
}

void	ft_commands_fill_list(t_program_data *data)
{
	t_token	*tmp;

	tmp = data->token_top;
	if (tmp->type >= REDIRECT_IN && tmp->type <= REDIRECT_APPEND)
		ft_commands_fill_list_r(data, tmp);
	else if (tmp->type == WORD)
		ft_commands_fill_list_c(data, tmp);
	else
		printf("ERROR\n");
	if ((tmp && tmp->next) && tmp->type == PIPE)
	{
		tmp = tmp->next;
		data->token_top = tmp;
		ft_commands_fill_list(data);
	}
}
