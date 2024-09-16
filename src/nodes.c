/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roko <roko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/09/03 16:41:13 by roko             ###   ########.fr       */
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
	{
		current = current->next;
	}
	current->next = new;
}
int	ft_new_token(char *token_name, t_program_data *data)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (1);
	new_token->content = ft_strdup(token_name);
	printf("added token: %s\n", new_token->content);
	new_token->type = 1;
	if (data->token_top == NULL)
	{
		new_token->next = NULL;
		new_token->prev = NULL;
		data->token_top = new_token;
	}
	else
	{
		ft_add_node(&data->token_top, new_token);
	}
	return (0);
}