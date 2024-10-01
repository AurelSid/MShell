/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/10/01 17:06:12 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// TABLEAU ENV!
int	main(int argc, char **argv, char **env)
{
	char			*rl;
	t_program_data	data;
	t_command		*tmp_cmd;

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
	if (rl)
		add_history(rl);
	if (rl == NULL)
		return (0);
	data.input = rl;
	ft_tokens_fill_list(&data);
	ft_print_tokens_list(data);
	ft_commands_fill_list(&data);
	ft_print_commands(data);
	ft_check_all_access(&data);
	tmp_cmd = data.command_top;
	while (tmp_cmd)
	{
		ft_apply_redir(tmp_cmd);
		ft_check_built_ins(tmp_cmd, &data);
		if (tmp_cmd->next != NULL)
		{
			fprintf(stderr, "\n\n-- executing [%s] pipe --\n\n", tmp_cmd->name);
			ft_exec_pipe(tmp_cmd, env);
		}
		else
		{
			fprintf(stderr, "\n\n-- executing [%s]  --\n\n", tmp_cmd->name);
			ft_exec_cmd(tmp_cmd, env);
		}
		fprintf(stderr, "\n-- [%s] OK --\n\n", tmp_cmd->name);
		tmp_cmd = tmp_cmd->next;
		// }
		// check_stdio_fds();
		// list_open_file_descriptors();
	}
	return (0);
}
