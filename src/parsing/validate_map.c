#include "../../includes/cub3d.h"

int check_config(char *line, t_game *game)
{
    if(ft_strncmp(line,"NO",3))
        game->config.no_path = ft_strdup(line + 3);
    else if(ft_strncmp(line,"SO",3))
        game->config.so_path = ft_strdup(line + 3);
    else if(ft_strncmp(line,"WE",3))
        game->config.we_path = ft_strdup(line + 3);    
    else if(ft_strncmp(line,"EA",3))
        game->config.ea_path = ft_strdup(line + 3);
    else if (line[0] == 'F')
        game->config.floor_color = ft_strdup(line + 2);
    else if (line[0] == 'C')
        game->config.ceiling_color = ft_strdup(line + 2);
    return (1);
}