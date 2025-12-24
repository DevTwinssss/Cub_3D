#include "../../includes/cub3d.h"

void add_line_map(char *line, t_game *game)
{
    char **new_grid;
    int i;

    new_grid = malloc(sizeof(char *) * (game->map.height + 2));
    if (!new_grid)
        exit(1);

    i = 0;
    while (i < game->map.height)
    {
        new_grid[i] = game->map.grid[i];
        i++;
    }

    new_grid[i] = ft_strdup(line);
    new_grid[i + 1] = NULL;

    free(game->map.grid);
    game->map.grid = new_grid;
    game->map.height++;
}
