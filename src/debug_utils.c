/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 18:30:57 by roko              #+#    #+#             */
/*   Updated: 2024/10/21 16:42:28 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_tokens_list(t_program_data data)
{
	t_token	*current;
	int		frame_width;

	current = data.token_top;
	frame_width = 50;
	printf("\n");
	printf("+");
	for (int i = 0; i < frame_width - 2; i++)
		printf("-");
	printf("+\n");
	printf("| %-46s |\n", "Token List");
	printf("|");
	for (int i = 0; i < frame_width - 2; i++)
		printf("-");
	printf("|\n");
	while (current)
	{
		printf("| Token content: %-30s || Type: %-2d |\n", current->content,
			current->type);
		current = current->next;
	}
	printf("+");
	for (int i = 0; i < frame_width - 2; i++)
		printf("-");
	printf("+\n");
}

void	ft_print_commands(t_program_data data)
{
	t_command		*cmd;
	t_redirection	*redir;
	int				frame_width;

	frame_width = 50;
	fprintf(stderr, "\n");
	fprintf(stderr, "+");
	for (int i = 0; i < frame_width - 2; i++)
		fprintf(stderr, "-");
	fprintf(stderr, "+\n");
	fprintf(stderr, "| %-46s |\n", "Commands List");
	fprintf(stderr, "|");
	for (int i = 0; i < frame_width - 2; i++)
		fprintf(stderr, "-");
	fprintf(stderr, "|\n");
	cmd = data.command_top;
	while (cmd)
	{
		fprintf(stderr, "| %-15s : %-30s |\n", "Command Name", cmd->name);
		fprintf(stderr, "| %-15s : %-30s |\n", "Arguments", cmd->args);
		fprintf(stderr, "| %-15s : %-30s |\n", "Options", cmd->options);
		fprintf(stderr, "| %-15s : %-30s |\n", "Path", cmd->path);
		redir = cmd->redirection_list;
		if (redir)
		{
			fprintf(stderr, "| %-15s : \n", "Redirections");
			while (redir)
			{
				fprintf(stderr, "| 	name: %-10s  type:%-3d file:%-3s\n |",
						redir->filename, redir->type, redir->filename);
				redir = redir->next;
			}
		}
		else
			fprintf(stderr, "| %-15s : %-30s |\n", "Redirections",
				"No redirections");
		cmd = cmd->next;
		fprintf(stderr, "|");
		for (int i = 0; i < frame_width - 2; i++)
			fprintf(stderr, "-");
		fprintf(stderr, "|\n");
	}
	fprintf(stderr, "+");
	for (int i = 0; i < frame_width - 2; i++)
		fprintf(stderr, "-");
	fprintf(stderr, "+\n");
}

void	ft_print_env(t_program_data data)
{
	t_env	*env;

	printf("\n------------------------------\n");
	printf("\n   Env copy list\n");
	env = data.env;
	while (env)
	{
		printf("%-30s : %s\n", env->var_name, env->content);
		env = env->next;
	}
}

void	list_open_file_descriptors(void)
{
	struct rlimit	rl;

	if (getrlimit(RLIMIT_NOFILE, &rl) == -1)
	{
		perror("getrlimit");
		return ;
	}
	printf("Open file descriptors:\n");
	for (rlim_t fd = 0; fd < rl.rlim_cur; fd++)
	{
		if (fcntl(fd, F_GETFD) != -1)
		{
			printf("File Descriptor %llu is open\n", (unsigned long long)fd);
		}
	}
	printf("\nClosed file descriptors cannot be listed since they are not accessible.\n");
}
void	check_stdio_fds(void)
{
	struct stat stdin_stat, stdout_stat;
	if (fstat(fileno(stdin), &stdin_stat) == -1)
	{
		perror("fstat(stdin)");
		return ;
	}
	if (fstat(fileno(stdout), &stdout_stat) == -1)
	{
		perror("fstat(stdout)");
		return ;
	}
	fprintf(stderr, "Standard Input (fd: %d):\n", fileno(stdin));
	fprintf(stderr, "  Type: %s\n",
		S_ISREG(stdin_stat.st_mode) ? "Regular file" : S_ISCHR(stdin_stat.st_mode) ? "Character device" : "Other");
	fprintf(stderr, "  Inode: %lu\n", (unsigned long)stdin_stat.st_ino);
	fprintf(stderr, "  Size: %lld bytes\n", (long long)stdin_stat.st_size);
	fprintf(stderr, "Standard Output (fd: %d):\n", fileno(stdout));
	fprintf(stderr, "  Type: %s\n",
		S_ISREG(stdout_stat.st_mode) ? "Regular file" : S_ISCHR(stdout_stat.st_mode) ? "Character device" : "Other");
	fprintf(stderr, "  Inode: %lu\n", (unsigned long)stdout_stat.st_ino);
	fprintf(stderr, "  Size: %lld bytes\n", (long long)stdout_stat.st_size);
	fprintf(stderr, " \n---------------------------------- \n");
}
