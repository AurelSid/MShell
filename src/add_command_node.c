/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/09/18 17:49:44 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_add_command(t_command **top, t_command *new)
{
	t_command	*current;

	if (!top || !new)
		return ;
	if (!(*top))
	{
		*top = new;
		return ;
	}
	current = *top;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new;
}

t_command	*ft_new_command(char *command_name, t_program_data *data,
		char *args, char *options)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (new_command == NULL)
		return (NULL);
	new_command->name = ft_strdup(command_name);
	new_command->args = ft_strdup(args);
	new_command->options = ft_strdup(options);
	new_command->redirection_list = NULL;
	if (data->token_top == NULL)
	{
		new_command->next = NULL;
		data->command_top = new_command;
	}
	else
	{
		ft_add_command(&data->command_top, new_command);
	}
	return (new_command);
}