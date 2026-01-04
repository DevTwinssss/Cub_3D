#include "../includes/cub3d.h"

int main(int ac, char **av)
{
	t_game *game;
    
    if (ac != 2)
    {
        printf("Usage: ./Cub3d <map.cub>\n");
        return (1);
    }
	game = malloc(sizeof(t_game));
    if (!game)
    {
        perror("Error Malloc failed\n");
        return (1);
    }
    init_game(game); // Set everything to NULL/0
    if (parsing(av[1], game) == -1)
    {
        cleanup_game(game);
        return (1);
    }
    check_map(game); 
	init_graphics(game);
	mlx_loop(game->mlx);
    cleanup_game(game);
	return(0);
}

