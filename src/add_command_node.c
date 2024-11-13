/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/12 15:54:53 by vpelc            ###   ########.fr       */
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
		current = current->next;
	current->next = new;
}

t_command	*ft_new_command(char *command_name,
		char *args, char *options)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (new_command == NULL)
		return (NULL);
	if (!command_name)
		new_command->name = NULL;
	else
		new_command->name = ft_strdup(command_name);
	new_command->options = ft_strdup(options);
	new_command->args = ft_strdup(args);
	new_command->redirection_list = NULL;
	new_command->next = NULL;
	new_command->path = NULL;
	new_command->input_fd = -100;
	new_command->output_fd = -100;
	new_command->ok = 0;
	if (g_data.command_top == NULL)
		g_data.command_top = new_command;
	else
		ft_add_command(&g_data.command_top, new_command);
	return (new_command);
}
