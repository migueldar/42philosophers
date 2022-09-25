NAME = philosophers
SRC = main.c utils.c exec.c philo_create_free.c process_create.c semaphore_create_destroy.c end.c philo_actions.c
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
RM = /bin/rm -rf
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	gcc $(OBJ) -o philosophers -fsanitize=thread
all: $(NAME)
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re