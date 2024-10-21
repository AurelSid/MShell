/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/10/21 17:49:39 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_program_data	data;
void	setup_pipe_and_redirect(void)
{
	int		pipe_fd[2];
	pid_t	process_id;

	if (pipe(pipe_fd) == -1)
	{
		exit(1);
	}
	process_id = fork();
	if (process_id == 0)
	{
		exit(0);
	}
	else
	{
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
		wait(NULL);
	}
}

void	ft_handle_signals(int signal)
{
	(void)signal;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
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
	//	ft_print_tokens_list(*data);
	ft_commands_fill_list(data);
	//	ft_print_commands(*data);
}
void	process_command(t_program_data *data, char **env)
{
	t_command	*tmp_cmd;

	tmp_cmd = data->command_top;
	while (tmp_cmd)
	{
		if (tmp_cmd->redirection_list == NULL)
			dup2(data->original_stdout, STDOUT_FILENO);
		if (ft_apply_redir(tmp_cmd, data))
		{
			if (tmp_cmd->next)
			{
				tmp_cmd->ok = -1;
				tmp_cmd = tmp_cmd->next;
				continue ;
			}
			else
				return ;
		}
		tmp_cmd = tmp_cmd->next;
	}
	tmp_cmd = data->command_top;
	while (tmp_cmd)
	{
		ft_last_redir(tmp_cmd->last_in, tmp_cmd->last_out, tmp_cmd);
		if (tmp_cmd->ok == 0)
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
			cleanup_and_exit(&data);
			clear_history();
			return (0);
		}
		if (rl[0] == '\0')
			continue ;
		handle_input(&data, rl);
		if (rl[0] == '\0')
			continue ;
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

// int	main(int argc, char **argv, char **env)
// {
// 	char			*rl;
// 	t_program_data	data;

// 	ft_setup_main(argc, argv, &data, env);
// 	// rl = readline("$> ");
// 	rl = "pwd";
// 	if (!rl)
// 	{
// 		ft_free_env(&data);
// 		clear_history();
// 		return (0);
// 	}
// 	handle_input(&data, rl);
// 	if (ft_check_all_access(&data))
// 	{
// 		cleanup_and_exit(&data);
// 	}
// 	process_command(&data, env);
// 	cleanup_and_exit(&data);
// 	// if (rl)
// 	// 	free(rl);
// 	ft_free_env(&data);
// 	system("leaks minishell");
// 	return (0);
// }
