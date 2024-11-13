/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirection_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/13 15:46:24 by asideris         ###   ########.fr       */
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

t_redirection	*ft_new_redirection(char *redirection_filename,
		t_redirection *r_list, int type)
{
	t_redirection	*new_redirection;

	new_redirection = malloc(sizeof(t_redirection));
	if (new_redirection == NULL)
		return (NULL);
	new_redirection->filename = ft_strtrim_args(redirection_filename, 0, 0);
	new_redirection->type = type;
	new_redirection->next = NULL;
	new_redirection->prev = NULL;
	if (r_list == NULL)
		r_list = new_redirection;
	else
		ft_add_redirection(&r_list, new_redirection);
	return (r_list);
}
