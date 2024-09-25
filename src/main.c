/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/09/25 15:54:19 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char				*rl;
	t_program_data		data;

	signal(SIGINT, ft_handle_signals);
	signal(SIGQUIT, SIG_IGN);
	data.token_top = NULL;
	if (argc != 1 || argv[1])
	{
		write(2, "Arg err\n", 8);
		return (0);
	}
	ft_init_data(&data);
	ft_env_copy(env, &data);
	// ft_print_env(data);
//	while (1)
//	{
		//rl = readline("$> ");
		rl = "export";
		if (rl == NULL)
			return (0);
		data.input = rl;
		// FAKE STRUCT TEST
		// ft_fake_list(&data);
		// ft_fake_command(&data, "cat", "test.txt", "-n -b");
		// ft_fake_command(&data, "ls", "", "-la");
		if (!ft_strcmp(rl, "export"))
			ft_export(NULL, &data);
		ft_tokens_fill_list(&data);
		ft_print_tokens_list(data);
		ft_commands_fill_list(&data);
		ft_print_commands(data);
		ft_check_all_access(&data);
//	}
	return (0);
}
