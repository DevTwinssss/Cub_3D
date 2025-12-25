#include "../../includes/cub3d.h"

int check_space(char *line)
{
    int i;

    i = 0;
    while(line[i] && line[i] != '\n')
    {
        if(line[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int help_parse_map(char *line, t_game *game, int *map_start, size_t len)
{
    if(len == 1 || check_space(line) == 1)
            return(0);
    if (!(*map_start) && is_config_line(line) == 0)
            check_config(line, game);
    else if (is_map_line(line))
    {
        *map_start = 1;
        add_line_map(line, game);
    }
    else if (*map_start)
    {
        printf("heere'n\n");
        return (-1);
    }
   
    return (0);
}

int parse_map(int fd, t_game *game)
{
    char *line;
    size_t len;
    int map_start;

    map_start = 0;
    game->map.width = 0;
    line = get_next_line(fd);
    while (line)
    {
        len = ft_strlen(line);
        if(help_parse_map(line, game, &map_start, len) == -1)
        {
            free(line);
            print_err("Map not valide !",game);
            return (-1);
        }
        if (game->map.width < (int)len)
            game->map.width = len - 2;
        free(line);
        line = get_next_line(fd);
    }
    return (0);
}