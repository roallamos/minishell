NAME = libft.a

CC = cc

AR = ar

CFLAGS = -Wall -Werror -Wextra

ARFLAGS  = -rcs

SOURCES = ft_atoi.c ft_calloc.c ft_isalpha.c ft_isdigit.c ft_memchr.c ft_memcpy.c ft_memset.c ft_strdup.c ft_strlcpy.c ft_strncmp.c ft_strcmp.c ft_strrchr.c ft_toupper.c ft_bzero.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_memcmp.c ft_memmove.c ft_strchr.c ft_strchr_null.c ft_strlcat.c ft_strlen.c ft_strnstr.c ft_tolower.c ft_substr.c ft_strjoin.c ft_strjoin_free.c ft_strtrim.c ft_split.c ft_strtok.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c get_next_line.c

BONUS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJECTS = $(SOURCES:.c=.o)

BONUS_OBJ = $(BONUS_SRC:.c=.o)

${NAME}: ${OBJECTS}	
	${AR} ${ARFLAGS} ${NAME} ${OBJECTS}

bonus: ${BONUS_OBJ}
	${AR} ${ARFLAGS} ${NAME} ${BONUS_OBJ}

clean:
	rm -f ${OBJECTS} ${BONUS_OBJ}

fclean: clean
	rm -f ${NAME}

all: ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
