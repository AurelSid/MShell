/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/13 16:05:25 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_program_data	g_data;

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

void	handle_input(char *rl)
{
	if (rl[0] == '\0')
	{
		ft_exit_free("");
		return ;
	}
	add_history(rl);
	g_data.input = rl;
	ft_tokens_fill_list();
	ft_commands_fill_list();
}

int	ft_setup_main(int argc, char **argv, char **env)
{
	if (argc != 1 || argv[1])
		return (0);
	initialize_signals();
	ft_init_data();
	if (!env[0])
		ft_env_empty();
	else
		ft_env_copy(env);
	g_data.original_stdin = dup(STDIN_FILENO);
	g_data.original_stdout = dup(STDOUT_FILENO);
	return (0);
}

int	main_loop(char *env[], char *rl)
{
	if (!rl)
	{
		ft_free_env();
		cleanup_and_exit();
		clear_history();
		exit(g_data.exit_status);
		return (0);
	}
	if (rl[0] == '\0')
		return (1);
	handle_input(rl);
	if (ft_check_all_access())
	{
		cleanup_and_exit();
		return (1);
	}
	process_command(env);
	cleanup_and_exit();
	if (rl)
		free(rl);
	system("leaks minishell");
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	*rl;

	ft_setup_main(argc, argv, env);
	i = 1;
	while (i == 1)
	{
		g_data.sig_int = 0;
		rl = readline("$> ");
		i = main_loop(env, rl);
	}
	return (0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	char	*rl;

// 	ft_setup_main(argc, argv, &g_data, env);
// 	while (1)
// 	{
// 		rl = "ls > tst";
// 		if (!rl)
// 		{
// 			ft_free_env(&g_data);
// 			cleanup_and_exit(&g_data);
// 			clear_history();
// 			exit(g_data.exit_status);
// 			return (0);
// 		}
// 		if (rl[0] == '\0')
// 			break ;
// 		handle_input(&g_data, rl);
// 		if (ft_check_all_access(&g_data))
// 		{
// 			cleanup_and_exit(&g_data);
// 			break ;
// 		}
// 		process_command(&g_data, env);
// 		break ;
// 	}
// 	cleanup_and_exit(&g_data);
// 	ft_free_env(&g_data);
// 	return (0);
// }
