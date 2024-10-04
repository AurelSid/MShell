/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/10/04 14:05:06 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

void	ft_initialize(t_program_data *data, int argc, char **argv, char **env)
{
	signal(SIGINT, ft_handle_signals);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	if (argc != 1 || argv[1])
	{
		write(2, "Arg err\n", 8);
		exit(0);
	}
	ft_init_data(data);
	ft_env_copy(env, data);
	data->original_stdin = dup(STDIN_FILENO);
	data->original_stdout = dup(STDOUT_FILENO);
}

int	ft_process_input(t_program_data *data)
{
	char	*rl;

	rl = readline("$> ");
	if (!rl)
		return (0);
	if (rl[0] != '\0')
		add_history(rl);
	data->input = rl;
	ft_tokens_fill_list(data);
	ft_commands_fill_list(data);
	return (1);
}

int	ft_execute_commands(t_program_data *data, char **env)
{
	t_command	*tmp_cmd;

	tmp_cmd = data->command_top;
	if (ft_check_all_access(data))
	{
		dup2(data->original_stdin, STDIN_FILENO);
		dup2(data->original_stdout, STDOUT_FILENO);
		ft_exit_free(data, "");
		return (1);
	}
	while (tmp_cmd)
	{
		ft_apply_redir(tmp_cmd);
		ft_exec(tmp_cmd, env, data);
		tmp_cmd = tmp_cmd->next;
	}
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
	ft_exit_free(data, "");
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_program_data	data;

	ft_initialize(&data, argc, argv, env);
	while (1)
	{
		if (!ft_process_input(&data))
			break ;
		if (ft_execute_commands(&data, env))
			continue ;
	}
	return (0);
}
