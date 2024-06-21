BLACK		= \033[0;30m
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
RESET		= \033[0m

CC 			= cc
CFLAGS		= -Wall -Wextra -Werror -I include
LIBS		= -L./libft -lft -lreadline

MANDATORY 	= src/main.c \
			src/signals.c	
EXECUTOR	= src/executor/ft_find_path.c \
			src/executor/ft_free.c \
			src/executor/ft_get_cmd.c \
			src/executor/ft_split_input.c \
			src/executor/ft_write_error.c \
			src/executor/execute_cmd.c \
			src/parse.c \
			src/executor/env_utils.c \
			src/executor/export.c \
			src/read/read_input.c
SRC 		= $(MANDATORY)$(EXECUTOR)
OBJS 		= $(SRC:.c=.o)
INCLS 		= -I include

NAME 		= minishell

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLS)

$(NAME): $(OBJS)
	@echo "$(BLUE)<----compiling libft---->$(RESET)"
	@(cd ./libft && make)
	@echo "$(GREEN)<----libft compiled!---->$(RESET)"
	@echo "$(YELLOW)****/compiling $(NAME)\****$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
	@echo "$(GREEN)****\$(NAME) compiled!/****$(RESET)"

all: $(NAME)

clean:
	@(cd ./libft && make clean)
	@rm -f $(OBJS) $(OBJS_BONUS)
	@echo "$(RED)--->objects deleted<----$(RESET)"

fclean: clean
	@(cd ./libft && make fclean)
	@rm -f $(NAME)
	@echo "$(RED)---->$(NAME) deleted<----$(RESET)"

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
