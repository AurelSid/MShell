/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:18:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/09/20 17:18:39 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
		/!\ LEAKS ON STRJOIN /!\
*/

void	ft_commands_fill_list(t_program_data *data)
{
	t_token		*tmp;
	t_command	*cmd;
	char		*opt;
	char		*args;

	if (data->token_top->type != WORD)
		printf("ERROR\n");
	opt = ft_calloc(1, 1);
	if (!opt)
		return ;
	args = ft_calloc(1, 1);
	if (!args)
		return ;
	tmp = data->token_top;
	tmp = tmp->next;
	while (tmp && (tmp->type == 1 && tmp->content[0] == '-'))
	{
		opt = ft_strjoin(opt, " ");
		opt = ft_strjoin(opt, tmp->content);
		tmp = tmp->next;
	}
	while (tmp && tmp->type == 1)
	{
		args = ft_strjoin(args, " ");
		args = ft_strjoin(args, tmp->content);
		tmp = tmp->next;
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
	if ((tmp && tmp->next) && tmp->type == PIPE)
	{
		tmp = tmp->next;
		data->token_top = tmp;
		ft_commands_fill_list(data);
	}
}

