/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:02:06 by brahimb           #+#    #+#             */
/*   Updated: 2024/10/22 14:08:03 by vpelc            ###   ########.fr       */
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
# include <termios.h>
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
	t_redirection			*last_in;
	t_redirection			*last_out;
	char					*path;
	int						ok;
}							t_command;
typedef struct s_token
{
	char					*content;
	int						type;
	struct s_token			*prev;
	struct s_token			*next;

}							t_token;
typedef struct s_env
{
	char					*var_name;
	char					*content;
	struct s_env			*next;
	struct s_env			*prev;
}							t_env;
typedef struct s_program_data
{
	t_token					*token_top;
	t_command				*command_top;

	char					*input;
	int						original_stdin;
	int						original_stdout;
	t_env					*env;
	int						exit_status;
	int						shell_lvl;
	pid_t					pid;
}							t_program_data;
extern t_program_data		data;

t_redirection				*ft_new_redirection(char *redirection_filename,
								t_redirection *r_list, int type);
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
int							ft_apply_redir(t_command *command,
								t_program_data *data);
int							ft_check_all_access(t_program_data *data);
void						ft_print_env(t_program_data data);
void						ft_add_env(t_env **lst, t_env *new);
int							ft_env_copy(char **env, t_program_data *data);
t_env						*ft_env_copy_2(t_env *env);
t_env						*ft_env_sort(t_env *env);
void						ft_commands_fill_list(t_program_data *data);
int							ft_init_data(t_program_data *data);
char						*ft_db_quotes(char *token, t_program_data *data);
char						*ft_spchar(char *token, t_program_data *data);
char						**ft_args_to_line(t_command *cmd);
// void						ft_checkspchar(char **var, int trim);

int							ft_exec(t_command *cmd, char **env,
								t_program_data *data);
void						ft_handle_signals(int signal);
void						ft_handle_signals_child(int signal);
int							ft_strcmp(const char *s1, const char *s2);
void						ft_limiter_exec(t_redirection *in, t_command *cmd);
void						list_open_file_descriptors(void);
void						check_stdio_fds(void);
int							ft_search_env(char **var, t_program_data data);

char						*ft_strjoin_free(char *s1, char *s2);
void						ft_free_split(char **tab);
void						ft_free_env(t_program_data *data);
char						*ft_strtrim_free(char *s1, char *set);

void						ft_env(t_command *cmd, t_program_data data);
void						ft_cd(t_command *cmd);
void						ft_echo(t_command *cmd);
void						ft_export(t_command *cmd, t_program_data *data);
void						ft_pwd(t_command *cmd);
void						ft_unset(t_command *cmd, t_program_data *data);
void						ft_exit(t_command *cmd, t_program_data data);

void						ft_clean_tokens(t_program_data *data);
void						ft_clean_commands(t_program_data *data);
void						ft_clean_redirections(t_command *cmd);
void						ft_exit_free(t_program_data *data, char *exit_msg);
void						ft_free_split(char **strs);

void						cleanup_and_exit(t_program_data *data);

void						send_error(char *error);
int							ft_set_cmd_path(t_program_data *data,
								char *cmd_name, char *path);
int							ft_check_absolute_p(t_command *cmd,
								t_program_data *data);

void						ft_exec_single_command(t_command *cmd, char **env,
								t_program_data *data);
void						ft_exec_piped_command(t_command *cmd, char **env,
								t_program_data *data);
int							ft_check_built_ins(char *cmd_name);
int							ft_exec_built_ins(t_command *cmd,
								t_program_data *data);
void						setup_pipe_and_redirect(void);
void						ft_checkspchar(char **var, t_program_data *data);
int							ft_handle_words(char *data, int index);
int							ft_handle_quotes(char *data, int index);
int							ft_last_redir(t_redirection *in, t_redirection *out,
								t_command *cmd, t_program_data *data);
int							ft_apply_redir_2(t_command *command,
								t_program_data *data);
void						ft_trimloop(char ***split);
char						**ft_split_args(char *args);

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