/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/09/20 17:09:49 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_add_node(t_token **top, t_token *new)
{
	t_token	*current;

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
	new->prev = current;
}

int	ft_new_token(char *token_name, t_program_data *data, int type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (1);
	new_token->content = ft_strdup(token_name);
	ft_db_quotes(new_token, *data);
	new_token->type = type;
	new_token->next = NULL;
	new_token->prev = NULL;
	if (data->token_top == NULL)
		data->token_top = new_token;
	else
		ft_add_node(&data->token_top, new_token);
	return (0);
}
