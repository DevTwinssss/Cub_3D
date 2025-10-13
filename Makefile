NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

SRC = src/main.c
MLX_DIR = minilibx-linux

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
