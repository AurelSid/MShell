/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:34:08 by roko              #+#    #+#             */
/*   Updated: 2024/11/14 13:31:32 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	ft_return_data()->input = rl;
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
	ft_return_data()->original_stdin = dup(STDIN_FILENO);
	ft_return_data()->original_stdout = dup(STDOUT_FILENO);
	return (0);
}

int	main_loop(char *env[], char *rl)
{
	if (!rl)
	{
		ft_free_env();
		cleanup_and_exit();
		clear_history();
		exit(ft_return_data()->exit_status);
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
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	*rl;

	ft_return_data();
	if (argc != 1)
	{
		write(2, "args error\n", 11);
		return (0);
	}
	ft_setup_main(argc, argv, env);
	i = 1;
	while (i == 1)
	{
		ft_return_data()->sig_int = 0;
		rl = readline("$> ");
		i = main_loop(env, rl);
	}
	return (0);
}

/* int	main(int argc, char **argv, char **env)
{
	char	*rl;

	ft_setup_main(argc, argv,env);
	while (1)
	{
		rl = "ls | wc";
		if (!rl)
		{
			ft_free_env();
			cleanup_and_exit();
			clear_history();
			exit(ft_return_data()->exit_status);
			return (0);
		}
		if (rl[0] == '\0')
			break ;
		handle_input(rl);
		if (ft_check_all_access())
		{
			cleanup_and_exit();
			break ;
		}
		process_command(env);
		break ;
	}
	cleanup_and_exit();
	system("leaks minishell");
	ft_free_env();
	return (0);
} */
