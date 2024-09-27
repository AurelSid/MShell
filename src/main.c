/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/09/27 16:55:17 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TABLEAU ENV!
int	main(int argc, char **argv, char **env)
{
	char			*rl;
	t_program_data	data;
	t_command		*tmp_cmd;

	// signal(SIGINT, ft_handle_signals);
	// signal(SIGQUIT, SIG_IGN);
	data.token_top = NULL;
	if (argc != 1 || argv[1])
	{
		write(2, "Arg err\n", 8);
		return (0);
	}
	ft_init_data(&data);
	ft_env_copy(env, &data);
	rl = readline("$> ");
	// while (1)
	// {
	data.input = rl;
	ft_tokens_fill_list(&data);
	ft_print_tokens_list(data);
	ft_commands_fill_list(&data);
	ft_check_all_access(&data);
	ft_print_commands(data);
	tmp_cmd = data.command_top;
	while (tmp_cmd)
	{
		// check_stdio_fds();
		ft_apply_redir(tmp_cmd);
		if (tmp_cmd->next != NULL)
		{
			fprintf(stderr, "\n\n--executing pipe--\n\n");
			ft_exec_pipe(tmp_cmd, env);
		}
		else
		{
			fprintf(stderr, "executing cmd\n");
			ft_exec_cmd(tmp_cmd, env);
		}
		printf("closing fds..\n");
		// close(tmp_cmd->input_fd);
		// close(tmp_cmd->output_fd);
		tmp_cmd = tmp_cmd->next;
		// }
		// check_stdio_fds();
		fprintf(stderr, "\n\n------------END OF COMMAND--------\n\n");
		// list_open_file_descriptors();
	}
	return (0);
}
