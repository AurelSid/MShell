/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/10/03 12:48:45 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TABLEAU ENV!
int	main(int argc, char **argv, char **env)
{
	char			*rl;
	t_program_data	data;
	t_command		*tmp_cmd;

	signal(SIGINT, ft_handle_signals);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	data.token_top = NULL;
	if (argc != 1 || argv[1])
	{
		write(2, "Arg err\n", 8);
		return (0);
	}
	ft_init_data(&data);
	ft_env_copy(env, &data);
	data.original_stdin = dup(STDIN_FILENO);
	data.original_stdout = dup(STDOUT_FILENO);
	while (1)
	{
		rl = readline("$> ");
		if (!rl)
			return (fprintf(stderr, "STDIN ERROR\n"));
		else
			add_history(rl);
		data.input = rl;
		ft_tokens_fill_list(&data);
		ft_commands_fill_list(&data);
		ft_print_commands(data);
		ft_check_all_access(&data);
		tmp_cmd = data.command_top;
		while (tmp_cmd)
		{
			ft_apply_redir(tmp_cmd);
			ft_exec(tmp_cmd, env, &data);
			tmp_cmd = tmp_cmd->next;
		}
		ft_exit_free(&data);
		dup2(data.original_stdin, STDIN_FILENO);
	}
	return (0);
}
