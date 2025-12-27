#include "../../includes/cub3d.h"

void init_game(t_game *game)
{
    game->config.no_path = NULL;
    game->config.so_path = NULL;
    game->config.we_path = NULL;
    game->config.ea_path = NULL;
    game->config.floor_color = 0;
    game->config.ceiling_color = 0;
    
    game->map.grid = NULL;
    game->map.width = 0;
    game->map.height = 0;
    
    game->mlx = NULL;
    game->win = NULL;
}

void free_config(t_config *config)
{
    if (config->no_path)
    {
        free(config->no_path);
        config->no_path = NULL;
    }
    if (config->so_path)
    {
        free(config->so_path);
        config->so_path = NULL;
    }
    if (config->we_path)
    {
        free(config->we_path);
        config->we_path = NULL;
    }
    if (config->ea_path)
    {
        free(config->ea_path);
        config->ea_path = NULL;
    }
        config->floor_color = 0;
        config->ceiling_color = 0;
}

void free_map(t_map *map)
{
    int i;

    if (map->grid)
    {
        i = 0;
        while (i < map->height && map->grid[i])
        {
            free(map->grid[i]);
            map->grid[i] = NULL;
            i++;
        }
        free(map->grid);
        map->grid = NULL;
    }
    map->height = 0;
    map->width = 0;
}

void cleanup_game(t_game *game)
{
    free_config(&game->config);
    free_map(&game->map);
    
    // If you're using MLX, uncomment these when you add MLX
    // if (game->win && game->mlx)
    //     mlx_destroy_window(game->mlx, game->win);
    // if (game->mlx)
    //     mlx_destroy_display(game->mlx);
    // if (game->mlx)
    //     free(game->mlx);
}

