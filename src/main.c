#include "../includes/cub3d.h"

int main(int ac, char **av)
{
    t_game game;

    if (ac != 2)
    {
        printf("Usage: ./Cub3d <map.ber>\n");
        return (1);
    }
    if (parsing(av[1],&game) == -1)
        return (1);
    return (0);
}

