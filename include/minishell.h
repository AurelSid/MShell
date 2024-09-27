/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:02:06 by brahimb           #+#    #+#             */
/*   Updated: 2024/09/27 15:05:28 by asideris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
//# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_redirection
{
	char					*filename;
	struct s_redirection	*next;
	struct s_redirection	*prev;
	int						type;
	int						direction;
}							t_redirection;

typedef struct s_command
{
	char					*name;
	struct s_command		*next;
	char					*args;
	char					*options;
	t_redirection			*redirection_list;
	int						output_fd;
	int						input_fd;
	char					*path;
}							t_command;
typedef struct s_token
{
	char					*content;
	int						type;
	char					*path;
	struct s_token			*prev;
	struct s_token			*next;

}							t_token;
typedef struct s_env
{
	char					*var_name;
	char					*content;
	struct s_env			*next;
}							t_env;
typedef struct s_program_data
{
	t_token					*token_top;
	t_command				*command_top;
	t_command				*first_cmd;
	char					*input;

	t_env					*env;
}							t_program_data;

int							ft_new_redirection(char *redirection_filename,
								t_command *command, int type);
void						ft_print_tokens(t_program_data *data);
void						ft_print_tokens_list(t_program_data data);
int							ft_new_token(char *token_name, t_program_data *data,
								int type);
void						ft_add_node(t_token **top, t_token *new);
int							ft_fake_list(t_program_data *data);
t_command					*ft_new_command(char *command_name,
								t_program_data *data, char *args,
								char *options);
void						ft_print_commands(t_program_data data);
int							ft_fake_command(t_program_data *data, char *name,
								char *options, char *args);
int							ft_tokens_fill_list(t_program_data *data);
int							ft_apply_redir(t_command *command);
int							ft_check_all_access(t_program_data *data);
void						ft_print_env(t_program_data data);
int							ft_env_copy(char **env, t_program_data *data);
void						ft_commands_fill_list(t_program_data *data);
int							ft_init_data(t_program_data *data);
void						ft_db_quotes(t_token *token, t_program_data data);
char						**ft_args_to_line(t_command *cmd);
int							ft_exec_cmd(t_command *cmd, char **env);
void						ft_exec_pipe(t_command *cmd, char **env);
void						ft_handle_signals(int signal);
int							ft_strcmp(const char *s1, const char *s2);
void						rl_replace_line(const char *text, int clear_undo);
void						ft_limiter_exec(t_redirection *in);
void						list_open_file_descriptors(void);
void						check_stdio_fds(void);

typedef enum s_token_type
{
	WORD = 1,
	SINGLE_QUOTE = 2,
	DOUBLE_QUOTE = 3,
	REDIRECT_IN = 4,
	REDIRECT_OUT = 5,
	REDIRECT_HEREDOC = 6,
	REDIRECT_APPEND = 7,
	PIPE = 8,
	INVALID = 9
}							t_type;
#endif