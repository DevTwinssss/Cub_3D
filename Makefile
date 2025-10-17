NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

SRC := $(wildcard src/*.c)\
	   $(wildcard src/utils/*.c)

MLX_DIR = minilibx-linux


%.o : %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
