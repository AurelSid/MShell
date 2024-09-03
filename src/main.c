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

int	ft_get_type(char *token)
{
	char	*quote;

	quote = "'";
	if (token == quote)
		return (SINGLE_QUOTE);
	return (0);
}
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
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (1);
	new_token->content = token_name;
	new_token->type = ft_get_type(token_name);
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
int	ft_tokens_fill_list(t_program_data *data)
{
	int	i;

	i = 0;
	while (data->tokens[i])
	{
		ft_new_token(data->tokens[i], data);
		i++;
	}
	ft_print_tokens(data);
	return (0);
}
int	main(int argc, char **argv)
{
	char			*rl;
	t_program_data	data;

	data.token_top = NULL;
	if (argc != 1 || argv[1])
	{
		write(2, "Arg err\n", 8);
		return (0);
	}
	rl = readline("$> ");
	data.tokens = ft_split(rl, ' ');
	ft_tokens_fill_list(&data);
	ft_print_tokens_list(data);
	return (0);
}
