/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/05 13:45:38 by vpelc            ###   ########.fr       */
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

int	ft_setup_main(int argc, char **argv, t_program_data *data, char **env)
{
	if (argc != 1 || argv[1])
		return (0);
	initialize_signals();
	ft_init_data(data);
	if (!env[0])
		ft_env_empty(data);
	else
		ft_env_copy(env, data);
	data->original_stdin = dup(STDIN_FILENO);
	data->original_stdout = dup(STDOUT_FILENO);
	return (0);
}

int	main_loop(t_program_data *data, char *env[], char *rl)
{
	if (!rl)
	{
		ft_free_env(data);
		cleanup_and_exit(data);
		clear_history();
		exit(data->exit_status);
		return (0);
	}
	if (rl[0] == '\0')
		return (1);
	handle_input(data, rl);
	if (ft_check_all_access(data))
	{
		cleanup_and_exit(data);
		return (1);
	}
	process_command(data, env);
	cleanup_and_exit(data);
	if (rl)
		free(rl);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	*rl;

	ft_setup_main(argc, argv, &g_data, env);
	i = 1;
	while (i == 1)
	{
		rl = readline("$> ");
		i = main_loop(&g_data, env, rl);
	}
	return (0);
}

/*  int	main(int argc, char **argv, char **env)
{
	char			*rl;

	ft_setup_main(argc, argv, &g_data, env);
	while (1)
	{
		rl = "ls -la";
		if (!rl)
		{
			ft_free_env(&g_data);
			cleanup_and_exit(&g_data);
			clear_history();
			exit(g_data.exit_status);
			return (0);
		}
		if (rl[0] == '\0')
			break ;
		handle_input(&g_data, rl);
		if (ft_check_all_access(&g_data))
		{
			cleanup_and_exit(&g_data);
			break ;
		}
		process_command(&g_data, env);
		cleanup_and_exit(&g_data);
		// if (rl)
		// 	free(rl);
		break ;
	}
	ft_free_env(&g_data);
	//system("leaks minishell");
	return (0);
} */
