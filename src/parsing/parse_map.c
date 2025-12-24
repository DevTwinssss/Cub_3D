#include "../../includes/cub3d.h"

int parse_map(int fd,t_game *game)
{
    char *line;

    line = get_next_line(fd);
    while (line != NULL)
    {
        check_config(line,game);
        
        printf("%s\n", line);
        free(line);
        line = get_next_line(fd);
    }
    return 0;
}
