/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/09/19 16:23:19 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_fake_list(t_program_data *data)
{
	int	i;

	i = 0;
	ft_new_token("cat", data, 1);
	ft_new_token("\"hello\"", data, 1);
	ft_new_token("|", data, 1);
	ft_new_token("wc", data, 1);
	ft_new_token("-l", data, 1);
	return (0);
}
int	ft_fake_command(t_program_data *data, char *name, char *options, char *args)
{
	printf("\nCreating new command\n\n");
	t_command *new_command;
	new_command = ft_new_command(name, data, args, options);
	printf("Adding redirections to command struct\n");
	ft_new_redirection("test.txt", new_command, REDIRECT_IN);

	return (0);
}