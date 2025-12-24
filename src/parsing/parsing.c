#include "../../includes/cub3d.h"

int parsing(char *str,t_game *game)
{
   int fd;

    game->map.grid = NULL;
    game->map.height = 0;
    fd = valide_name(str);
    if(fd < 0)
        return (-1);
    parse_map(fd,game);
    
    close(fd);
    return (0);
}
