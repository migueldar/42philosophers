NAME = philosophers
SRC = main.c utils.c exec.c philo_create_free.c thread_create_free.c ft_usleep.c
CFLAGS = -Wall -Wextra -Werror
RM = /bin/rm -rf
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	gcc $(OBJ) -o philosophers
all: $(NAME)
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re