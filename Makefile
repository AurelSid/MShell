NAME = minishell

DIR_SOURCES = src/

MY_SOURCES 		= main.c add_token_node.c atol.c \
				add_command_node.c add_redirection_node.c token.c env_supp_2.c\
 				apply_redirections.c check_access.c command.c env.c env_supp.c \
				init_data.c quotes.c  utils.c utils_2.c\
				\
				 builtins/env.c builtins/echo.c builtins/pwd.c builtins/export.c \
				builtins/cd.c builtins/exit.c builtins/unset.c  builtins/export_var.c \
				\
				here_doc.c exec_command.c clear_commands.c env_to_tab.c\
				exit.c free.c check_access_utils.c split_args.c \
				exec_pipe_command.c spchar.c spchar_2.c exec_single_command.c\
				commands_fill_list_r.c open_file.c signals.c process_command.c\
				open_files_supp.c exec_command_supp.c exec_single_command_supp.c


SOURCES = $(addprefix $(DIR_SOURCES), $(MY_SOURCES))

MY_OBJECTS = $(SOURCES:.c=.o)

C_GREEN = \033[0;32m

C_RED = \033[0;31m

C_BLUE = \033[0;34m

C_BPURP = \033[1;35m

C_END =	\033[0m

CFLAGS = -Wall -Werror -Wextra

# ifeq "$(USER)" ""
READLINE_PATH = $(HOME)/.brew/Cellar/readline/8.2.13/
# else
# 	#READLINE_PATH = /opt/homebrew/Cellar/readline/8.2.10/
# 	READLINE_PATH = $(HOME)/homebrew/Cellar/readline/8.2.10/
# endif

INCLUDES = ./include -I$(READLINE_PATH)/include

LIBFT = ./include/libft

LFLAGS = -lreadline -lhistory -L$(READLINE_PATH)/lib

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	@make -C $(LIBFT)
	@gcc $(CFLAGS) $(LFLAGS) -o $(NAME) $(MY_OBJECTS) $(LIBFT)/libft.a

%.o:	%.c
	@gcc $(CFLAGS) -I $(INCLUDES) -c $< -o $@

add:
	git add Makefile src includes main.c .gitignore

clean:
	@rm -rf $(MY_OBJECTS)
	@make -j 3 -C $(LIBFT) clean
	@rm -rf ./includes/ee/*.sh
	@echo "$(C_RED)$(NAME) cleanse$(C_END)"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)/libft.a
	@echo "$(C_RED)$(C_END)"

re: fclean all

debug: re
debug: CFLAGS += -g3 -D DEBUG=1