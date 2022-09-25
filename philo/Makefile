NAME = philosophers
SRC = main.c utils.c exec.c philo_create_free.c philo_create_free2.c thread_create_free.c utils2.c
CFLAGS = -Wall -Wextra -Werror -O3
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