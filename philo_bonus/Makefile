NAME = philosophers
SRC = main.c utils.c exec.c philo_create_free.c process_create.c ft_usleep.c semaphore_create_destroy.c
CFLAGS = -Wall -Wextra -Werror -O3 -lpthread
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