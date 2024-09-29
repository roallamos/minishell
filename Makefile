BLACK		=	$(shell tput setaf 0)
RED			=	$(shell tput setaf 1)
GREEN		=	$(shell tput setaf 2)
YELLOW		=	$(shell tput setaf 3)
BLUE		=	$(shell tput setaf 4)
MAGENTA		=	$(shell tput setaf 5)
CYAN		=	$(shell tput setaf 6)
WHITE		=	$(shell tput setaf 7)
BOLD        =	$(shell tput bold)
UNDERLINE   =	$(shell tput smul)
REVERSE     =	$(shell tput rev)
BLINK       =	$(shell tput blink)
DIM         =	$(shell tput dim)
STANDOUT    =	$(shell tput smso)
RESET		=	$(shell tput sgr0)

CC 			=	cc
CFLAGS		=	-Wall -Wextra -Werror -I include -g3 -fsanitize=address
LIBS		=	-L./libft -lft -lreadline

MANDATORY 	=	src/main.c \
			src/signals.c	
EXECUTOR	=	src/executor/do_cd.c \
			src/executor/do_exit.c \
			src/executor/env_utils.c \
			src/executor/execute_cmd.c \
			src/executor/execute.c \
			src/executor/export.c \
			src/executor/do_unset.c \
			src/executor/do_echo.c \
			src/executor/ft_find_path.c \
			src/executor/ft_get_cmd.c \
			src/executor/ft_pwd.c \
			src/executor/ft_write_error.c \
			src/frees/ft_free.c \
			src/pipex/files_manage.c \
			src/pipex/ft_pipex.c \
			src/pipex/redirections.c \
			src/pipex/utils.c \
			src/read/check_input.c \
			src/read/expand.c \
			src/read/ft_split_args.c \
			src/read/ft_split_input.c \
			src/read/lists.c \
			src/read/prepare_input.c \
			src/read/read_input.c \
			src/read/set_prompt.c \
			src/read/parse_utils.c 
SRC 		=	$(MANDATORY)$(EXECUTOR)
OBJS 		=	$(SRC:.c=.o)
INCLS 		=	-I include

NAME 		=	minishell

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLS)

$(NAME): $(OBJS)
	@echo "$(CYAN)$(BOLD) <----compiling libft---->$(RESET)"
	@(cd ./libft && make)
	@echo "$(GREEN)$(BOLD) <----libft compiled!---->$(RESET)"
	@echo "$(WHITE)$(BOLD)·----------------------------·$(RESET)"
	@echo "$(YELLOW)$(BOLD)$(UNDERLINE) ****/compiling $(NAME)\****$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
	@echo "$(GREEN)$(BOLD)$(REVERSE) ****\$(NAME) compiled!/****$(RESET)"

all: $(NAME)

clean:
	@(cd ./libft && make clean)
	@rm -f $(OBJS) $(OBJS_BONUS)
	@echo "$(RED)$(BOLD)$(DIM) --->objects deleted<----$(RESET)"

fclean: clean
	@(cd ./libft && make fclean)
	@rm -f $(NAME)
	@echo "$(RED)$(BOLD)$(REVERSE) ---->$(NAME) deleted<----$(RESET)"

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
