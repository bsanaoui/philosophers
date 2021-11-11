.PHONY: all fclean clean re bonus
NAME = philo

CC = gcc -g -fsanitize=address
FLAGS = -Werror -Wextra -Wall

SRC = $(wildcard src/*.c)

all : $(NAME)

$(NAME): $(SRC)
		@$(CC) $(SRC) -I $(FLAGS) -o $(NAME)

fclean: clean
		@rm -f $(NAME)

clean:
		@rm -f *.o

re: fclean all

push:
		@git add .
		@git commit -m "$(m)"
		git push origin

main:
		@make re && ./philo $(args)