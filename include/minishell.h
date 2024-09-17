/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asideris <asideris@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:02:06 by brahimb           #+#    #+#             */
/*   Updated: 2024/09/17 11:58:05 by asideris         ###   ########.fr       */
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

typedef struct s_command
{
	char				*cmd_name;
	int					type;
	struct s_command	*next;
	char				**comd_args;
}						t_command;
typedef struct s_token
{
	char				*content;
	int					type;
	struct s_token		*prev;
	struct s_token		*next;

}						t_token;
typedef struct s_program_data
{
	int					comd_count;
	t_token				*token_top;
	int					token_count;
	t_command			first_cmd;
	t_command			last_cmd;
	char				**tokens;
	char				*input;
}						t_program_data;
void					ft_print_tokens(t_program_data *data);
void					ft_print_tokens_list(t_program_data data);
int						ft_new_token(char *token_name, t_program_data *data);
void					ft_add_node(t_token **top, t_token *new);

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
}						t_type;
#endif