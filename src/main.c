#include "../includes/cub3d.h"

int main(int ac, char **av)
{
    t_game game;
    int i;
    
    init_game(&game);
    
    if (ac != 2)
    {
        printf("Usage: ./Cub3d <map.cub>\n");
        return (1);
    }
    if (parsing(av[1], &game) == -1)
    {
        cleanup_game(&game);
        return (1);
    }
    check_map(&game);

    i = 0;
    while (game.map.grid && game.map.grid[i])
    {
        printf("%s\n", game.map.grid[i]);
        i++;
    }  
    cleanup_game(&game);
    return (0);
}
