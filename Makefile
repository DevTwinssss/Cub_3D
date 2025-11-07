NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

SRC := $(wildcard src/*.c) \
       $(wildcard src/raycasting/*.c)

OBJ = $(SRC:.c=.o)

MLX_DIR = minilibx-linux

%.o: %.c 
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
