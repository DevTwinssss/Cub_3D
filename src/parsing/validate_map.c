#include "../../includes/cub3d.h"

int check_config(char *line, t_game *game)
{
    if(ft_strncmp(line,"NO ",3) == 0)
        game->config.no_path = ft_strdup(line + 3);
    else if(ft_strncmp(line,"SO ",3) == 0)
        game->config.so_path = ft_strdup(line + 3);
    else if(ft_strncmp(line,"WE ",3) == 0)
        game->config.we_path = ft_strdup(line + 3);    
    else if(ft_strncmp(line,"EA ",3) == 0)
        game->config.ea_path = ft_strdup(line + 3);
    else if (line[0] == 'F')
        game->config.floor_color_char = ft_strdup(line + 2);
    else if (line[0] == 'C')
        game->config.ceiling_color_char = ft_strdup(line + 2);
    else
        return (0);
    return (1);
}

int is_map_line(char *line)
{
    int i = 0;

    if (!line || line[0] == '\n')
        return (0);

    while (line[i])
    {
        if (!ft_strchr("01NSEW \n\r", line[i]))
            return (0);
        i++;
    }
    return (1);
}


int check_map(char *line)
{
    int i;

    i = 0;
    while(line[i])
    {
        if(strchr("01NSEW \n",line[i]))
            return(0);
        i++;
    }
    return(1);
}

int is_config_line(char *line)
{
    return (ft_strncmp(line, "NO ", 3) == 0 ||
            ft_strncmp(line, "SO ", 3) == 0 ||
            ft_strncmp(line, "WE ", 3) == 0 ||
            ft_strncmp(line, "EA ", 3) == 0 ||
            ft_strncmp(line, "F ", 2) == 0 ||
            ft_strncmp(line, "C ", 2) == 0);
}


