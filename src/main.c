/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/09/20 13:32:41 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char			*rl;
	t_program_data	data;

	data.token_top = NULL;
	if (argc != 1 || argv[1])
	{
		write(2, "Arg err\n", 8);
		return (0);
	}
	ft_init_data(&data);
	ft_env_copy(env, &data);
	// ft_print_env(data);
	rl = readline("$> ");
	//rl = "cat lol | cat lol";
	data.input = rl;
	// FAKE STRUCT TEST
	//-------------------------
	// ft_fake_list(&data);
	// ft_fake_command(&data, "cat", "test.txt", "-n -b");
	// ft_fake_command(&data, "ls", "", "-la");
	//-------------------------
	ft_tokens_fill_list(&data);
	ft_print_tokens_list(data);
	//-------------------------
	ft_commands_fill_list(&data);
	ft_print_commands(data);
	return (0);
}
