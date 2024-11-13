/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpelc <vpelc@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:02:06 by brahimb           #+#    #+#             */
/*   Updated: 2024/11/12 16:06:23 by vpelc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
//# include <stdlib.h>
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
	int						child;
	int						sig_int;
}							t_program_data;
extern t_program_data		g_data;

t_redirection				*ft_new_redirection(char *redirection_filename,
								t_redirection *r_list, int type);
void						ft_print_tokens(void);
void						ft_print_tokens_list();
int							ft_new_token(char *token_name, int type);
void						ft_add_node(t_token **top, t_token *new);
int							ft_fake_list(void);
t_command					*ft_new_command(char *command_name, char *args,
								char *options);
void						ft_print_commands();
int							ft_fake_command(char *name, char *options,
								char *args);
int							ft_tokens_fill_list(void);
int							ft_apply_redir(t_command *command);
int							ft_check_all_access(void);
void						ft_print_env();
void						ft_add_env(t_env **lst, t_env *new);
int							ft_env_copy(char **env);
t_env						*ft_env_copy_2(t_env *env);
t_env						*ft_env_sort(t_env *env);
void						ft_commands_fill_list(void);
int							ft_init_data(void);
char						*ft_db_quotes(char *token);
char						*ft_spchar(char *token);
char						**ft_args_to_line(t_command *cmd);
// void						ft_checkspchar(char **var, int trim);

int							ft_exec(t_command *cmd, char **env);
void						ft_handle_signals(int signal);
void						ft_handle_signals_child(int signal);
int							ft_strcmp(const char *s1, const char *s2);
void						ft_limiter_exec(t_redirection *in, t_command *cmd);
void						list_open_file_descriptors(void);
void						check_stdio_fds(void);
int							ft_search_env(char **var);

char						*ft_strjoin_free(char *s1, char *s2);
void						ft_free_split(char **tab);
void						ft_free_env(void);
char						*ft_strtrim_free(char *s1, char *set);
long						ft_atol(const char *str);

void						ft_env(t_command *cmd);
void						ft_cd(t_command *cmd);
void						ft_echo(t_command *cmd);
void						ft_export(t_command *cmd);
void						ft_pwd(t_command *cmd);
void						ft_unset(t_command *cmd);
void						ft_exit(t_command *cmd);

void						ft_clean_tokens(void);
void						ft_clean_commands(void);
void						ft_clean_redirections(t_command *cmd);
void						ft_exit_free(char *exit_msg);
void						ft_free_split(char **strs);

void						cleanup_and_exit(void);

int							ft_set_cmd_path(char *cmd_name, char *path);
int							ft_check_absolute_p(t_command *cmd);

void						ft_exec_single_command(t_command *cmd, char **env);
void						ft_exec_piped_command(t_command *cmd, char **env);
int							ft_check_built_ins(char *cmd_name);
int							ft_exec_built_ins(t_command *cmd);
void						setup_pipe_and_redirect(void);
void						ft_checkspchar(char **var);
char						*ft_check_exitsp(char *arg);
int							ft_handle_words(char *data, int index);
int							ft_handle_quotes(char *data, int index);
int							ft_last_redir(t_redirection *in, t_redirection *out,
								t_command *cmd);
int							ft_apply_redir_2(t_command *command);
void						ft_trimloop(char ***split);
char						**ft_split_args(char *args);
char						**ft_split_args_2(char *args);
char						*ft_strtrim_args(char *str);
void						ft_export_trim(char ***args);
t_token						*ft_commands_fill_list_r(t_token *tmp, char **args,
								char **opt);
int							ft_check_redir(t_token **tmp, t_redirection **redir);
int							ft_check_opt(t_token **tmp, char *cmd_n,
								char **opt);
int							ft_check_args(t_token **tmp, char *cmd_n,
								char **args);
int							ft_open_file(t_command *cmd);

int							ft_specific_error(const char *filename);
void						ft_export_var(char *arg);
t_env						*ft_env_exist(char *var);
int							ft_valid_var(char *var);
char						*ft_spchar(char *var);
int							ft_handle_words(char *var, int index);
char						*ft_spcharloop(char *args);
int							ft_while_cmd(t_command *cmd, char **split_paths);
void						ft_while_cmd_supp(t_command *cmd,
								char **split_paths);
int							ft_while_split(char **split_paths, t_command *cmd,
								int *found_working_path);
void						process_command(char **env);
void						initialize_signals(void);
// OPEN FILES FUNCTIONS
int							ft_handle_redirect_in(t_command *cmd,
								t_redirection *redir);
int							ft_handle_redirect_out(t_command *cmd,
								t_redirection *redir);
int							ft_handle_redirect_append(t_command *cmd,
								t_redirection *redir);
void						ft_handle_heredoc(t_redirection *redir,
								t_command *cmd);
void						ft_handle_child_sig(int err);
//
int							ft_check_built_ins(char *cmd_name);
int							ft_exec_built_ins(t_command *cmd);
int							ft_exec_built_ins_in_pipe(t_command *cmd);
void						ft_pwd_setup(t_env **env, char *type);
void						ft_env_empty(void);
char						**ft_env_to_tab(char **tab);

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