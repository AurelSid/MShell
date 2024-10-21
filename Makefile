NAME = minishell

MY_SOURCES =	src/debug_utils.c src/add_token_node.c \
				src/add_command_node.c src/add_redirection_node.c src/token.c \
 				src/apply_redirections.c src/check_access.c src/command.c src/env.c \
				src/init_data.c src/quotes.c  src/utils.c  src/builtins/env.c\
				src/builtins/echo.c src/builtins/pwd.c src/builtins/export.c \
				src/builtins/cd.c src/builtins/exit.c src/builtins/unset.c \
				src/here_doc.c src/exec_command.c src/clear_commands.c \
				src/exit.c src/free.c src/check_access_utils.c src/main.c src/exec_single_command.c \
				src/exec_pipe_command.c src/spchar.c
				

MY_OBJECTS = $(MY_SOURCES:.c=.o)

C_GREEN = \033[0;32m

C_RED = \033[0;31m

C_BLUE = \033[0;34m

C_BPURP = \033[1;35m

C_END=\033[0m

CFLAGS = #-Wall -Werror -Wextra

# ifeq "$(USER)" "lvodak"
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
debug: CFLAGS += -g3 -D DEBUG=1 #-fsanitize=address 

.PHONY: all clean fclean re debug