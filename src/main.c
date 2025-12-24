#include "../includes/cub3d.h"

#include "../includes/cub3d.h"

int main(int ac, char **av)
{
    t_game game;
    int i;

    if (ac != 2)
    {
        printf("Usage: ./Cub3d <map.cub>\n");
        return (1);
    }
    if (parsing(av[1], &game) == -1)
        return (1);

    i = 0;
    while (game.map.grid && game.map.grid[i])
    {
        printf("main struct => %s\n", game.map.grid[i]);
        i++;
    }
    return (0);
}


