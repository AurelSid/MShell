/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/10/11 17:26:57 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_handle_signals(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
void	initialize_signals(void)
{
	signal(SIGINT, ft_handle_signals);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	handle_input(t_program_data *data, char *rl)
{
	if (rl[0] == '\0')
	{
		ft_exit_free(data, "");
		return ;
	}
	add_history(rl);
	data->input = rl;
	ft_tokens_fill_list(data);
	ft_commands_fill_list(data);
}

void	process_command(t_program_data *data, char **env)
{
	t_command	*tmp_cmd;

	tmp_cmd = data->command_top;
	while (tmp_cmd)
	{
		if (ft_apply_redir(tmp_cmd, data))
			break ;
		ft_exec(tmp_cmd, env, data);
		tmp_cmd = tmp_cmd->next;
	}
}
int	ft_setup_main(int argc, char **argv, t_program_data *data, char **env)
{
	if (argc != 1 || argv[1])
		return (0);
	initialize_signals();
	ft_init_data(data);
	ft_env_copy(env, data);
	data->original_stdin = dup(STDIN_FILENO);
	data->original_stdout = dup(STDOUT_FILENO);
	return (0);
}
int	main(int argc, char **argv, char **env)
{
	char			*rl;
	t_program_data	data;

	ft_setup_main(argc, argv, &data, env);
	while (1)
	{
		rl = readline("$> ");
		if (!rl)
		{
			ft_free_env(&data);
			clear_history();
			system("leaks minishell");
			return (0);
		}
		handle_input(&data, rl);
		if (ft_check_all_access(&data))
		{
			cleanup_and_exit(&data);
			continue ;
		}
		process_command(&data, env);
		cleanup_and_exit(&data);
		if (rl)
			free(rl);
	}
	ft_free_env(&data);
	return (0);
}
