/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/09/18 16:53:43 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_add_redirection(t_redirection **top, t_redirection *new)
{
	t_redirection	*current;

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

int	ft_new_redirection(char *redirection_filename, t_command *command, int type)
{
	t_redirection	*new_redirection;

	new_redirection = malloc(sizeof(t_redirection));
	if (new_redirection == NULL)
		return (1);
	new_redirection->filename = ft_strdup(redirection_filename);
	new_redirection->type = type;
	if (command->redirection_list == NULL)
	{
		new_redirection->next = NULL;
		new_redirection->prev = NULL;
		command->redirection_list = new_redirection;
	}
	else
	{
		ft_add_redirection(&command->redirection_list, new_redirection);
	}
	return (0);
}
