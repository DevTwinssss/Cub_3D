#include "../../includes/cub3d.h"

void add_line_map(char *line, t_game *game)
{
    char **new_grid;
    char *cleaned_line;
    int i;
    int len;

    new_grid = malloc(sizeof(char *) * (game->map.height + 2));
    if (!new_grid)
        exit(1);

    i = 0;
    while (i < game->map.height)
    {
        new_grid[i] = game->map.grid[i];
        i++;
    }

    // Remove \r and \n from the nd of the line
    cleaned_line = ft_strdup(line);
    len = ft_strlen(cleaned_line);
    while (len > 0 && (cleaned_line[len - 1] == '\n' || cleaned_line[len - 1] == '\r'))
    {
        cleaned_line[len - 1] = '\0';
        len--;
    }

    new_grid[i] = cleaned_line;
    new_grid[i + 1] = NULL;

    free(game->map.grid);
    game->map.grid = new_grid;
    game->map.height++;
}
