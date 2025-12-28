#include "../../includes/cub3d.h"

void validate_config(t_game *game)
{
    if (!game->config.no_path)
        print_err("Missing NO texture path", game);
    if (!game->config.so_path)
        print_err("Missing SO texture path", game);
    if (!game->config.we_path)
        print_err("Missing WE texture path", game);
    if (!game->config.ea_path)
        print_err("Missing EA texture path", game);
    if (!game->config.floor_color)
        print_err("Missing F color", game);
    if (!game->config.ceiling_color)
        print_err("Missing C color", game);
}

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
        game->config.floor_color = parse_color(line + 2);
    else if (line[0] == 'C')
        game->config.ceiling_color = parse_color(line + 2);
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

int is_config_line(char *line, t_game *game)
{
    if(ft_strncmp(line, "NO ", 3) == 0)
        game->flag.NO++;
    else if(ft_strncmp(line, "SO ", 3) == 0)
        game->flag.SO++;
    else if(ft_strncmp(line, "EA ", 3) == 0)
        game->flag.EA++;
    else if(ft_strncmp(line, "WE ", 3) == 0)
        game->flag.WE++;
    else if(ft_strncmp(line, "F ", 2) == 0)
        game->flag.F++;
    else if(ft_strncmp(line, "C ", 2) == 0)
        game->flag.C++;
    else
        return(1);
    return(0);
}


