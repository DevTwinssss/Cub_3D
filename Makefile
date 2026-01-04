NAME = cub3d
CC = cc
CFLAGS = -Werror -Wextra -Wall #-g -fsanitize=address 

SRC := 	$(wildcard src/parsing/*.c) \
		$(wildcard src/utils/*.c) \
		$(wildcard src/parsing/checks/*.c) \
		$(wildcard src/garbage_collec/*.c) \
		$(wildcard get_next_line/*.c) \
		$(wildcard src/*.c) \
      	$(wildcard src/raycasting/*.c)

OBJ = $(SRC:.c=.o)

MLX_DIR = minilibx-linux

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -I$(MLX_DIR) -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz -o $(NAME)

# depand on header file
%.o: %.c 
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)

