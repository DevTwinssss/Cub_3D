#include "../../includes/cub3d.h"

void print_err(char *err, t_game *game)
{
    printf("Error: %s\n", err);
    cleanup_game(game);
    exit(1);
}