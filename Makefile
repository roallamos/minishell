BLACK		=	$(shell tput setaf 0)
RED			=	$(shell tput setaf 1)
GREEN		=	$(shell tput setaf 2)
YELLOW		=	$(shell tput setaf 3)
BLUE		=	$(shell tput setaf 4)
MAGENTA		=	$(shell tput setaf 5)
CYAN		=	$(shell tput setaf 6)
WHITE		=	$(shell tput setaf 7)
RESET		=	$(shell tput sgr0)

CC 			=	cc
CFLAGS		=	-Wall -Wextra -Werror -I include
LIBS		=	-L./libft -lft -lreadline

MANDATORY 	=	src/main.c \
			src/signals.c	
EXECUTOR	=	src/executor/ft_find_path.c \
			src/executor/ft_free.c \
			src/executor/ft_get_cmd.c \
			src/executor/ft_split_input.c \
			src/executor/ft_write_error.c \
			src/executor/execute_cmd.c \
			src/parse.c \
			src/executor/env_utils.c \
			src/executor/export.c \
			src/read/read_input.c \
			src/read/check_input.c \
			src/executor/ft_pwd.c \
			src/executor/set_prompt.c \
			src/executor/do_exit.c \
			src/executor/do_cd.c
SRC 		=	$(MANDATORY)$(EXECUTOR)
OBJS 		=	$(SRC:.c=.o)
INCLS 		=	-I include

NAME 		=	minishell

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
