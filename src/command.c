/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:18:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/09/19 12:33:19 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
		/!\ LEAKS ON STRJOIN /!\
*/

void	ft_commands_fill_list(t_program_data *data)
{
	t_token	*tmp;
	char	*opt;
	char	*args;

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
	while (tmp->next && (tmp->type == 1 && tmp->content[0] == '-'))
	{
		opt = ft_strjoin(opt, ' ');
		opt = ft_strjoin(opt, tmp->content);
		tmp = tmp->next;
	}
	while (tmp->next && tmp->type == 1)
	{
		args = ft_strjoin(args, ' ');
		args = ft_strjoin(args, tmp->content);
		tmp = tmp->next;
	}
	/* 	if (tmp->type == 4 || tmp->type == 5 || tmp->type == 6
			|| tmp->type == 7)
			//add_redirection(ft_new_command(data->token_top->content, data,
					args, opt));*/
}
