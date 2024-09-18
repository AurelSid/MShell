/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:18:21 by vpelc             #+#    #+#             */
/*   Updated: 2024/09/18 17:45:20 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_command	*ft_new_command(char *cmd_name, t_program_data *data,
	char *args, char *opt)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_token));
	if (new_command == NULL)
		return (NULL);
	new_command->cmd_name = ft_strdup(cmd_name);
	new_command->comd_args = ft_strdup(args);
	new_command->options = ft_strdup(opt);
	new_command->next = NULL;
	if (data->token_top == NULL)
	{
		data->token_top = new_command;
	}
	else
		ft_add_node(&data->token_top, new_command);
	return (new_command);
}

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
/* 	if (tmp->type == 4 || tmp->type == 5 || tmp->type == 6 || tmp->type == 7)
		//add_redirection(ft_new_command(data->token_top->content, data, args, opt));*/
}
