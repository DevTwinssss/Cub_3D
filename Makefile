NAME = Cub3d
CC = cc
CFLAGS = -Werror -Wextra -Wall -g #-fsanitize=address 

SRC := 	$(wildcard src/parsing/*.c) \
		$(wildcard src/utils/*.c) \
		$(wildcard get_next_line/*.c) \
		$(wildcard src/*.c) \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS)  $(OBJ) -o $(NAME) -lreadline

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)