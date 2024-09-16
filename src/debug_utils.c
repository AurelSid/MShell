/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roko <roko@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:30:57 by roko              #+#    #+#             */
/*   Updated: 2024/09/03 16:40:12 by roko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_tokens_list(t_program_data data)
{
	printf("Token List\n");
	while (data.token_top->next)
	{
		printf("Token content: %s  || Token type: %d\n",
			data.token_top->content, data.token_top->type);
		data.token_top = data.token_top->next;
	}
	printf("Token content: %s  || Token type: %d\n", data.token_top->content,
		data.token_top->type);
}
