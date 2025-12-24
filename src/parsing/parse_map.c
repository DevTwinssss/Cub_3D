#include "../../includes/cub3d.h"

int parse_map(int fd, t_game *game)
{
    char *line;
    int map_started;

    map_started = 0;
    line = get_next_line(fd);
    while (line)
    {
        if (!map_started && is_config_line(line))
            check_config(line, game);
        else if (is_map_line(line))
        {
            map_started = 1;
            add_line_map(line, game);
        }
        else if (map_started)
        {
            free(line);
            return (-1);
        }
        free(line);
        line = get_next_line(fd);
    }
    return (0);
}

