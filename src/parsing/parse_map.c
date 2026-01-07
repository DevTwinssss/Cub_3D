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
    if (!(*map_start) && is_config_line(line, game) == 0)
            check_config(line, game);
    else if (is_map_line(line))
    {
        *map_start = 1;
        add_line_map(line, game);
    }
    else if (*map_start)
        return (-1);   
    return (0);
}
void flag_check(t_game *game)
{
    if(game->flag.no > 1 || game->flag.so > 1
        || game->flag.we > 1 || game->flag.ea > 1 || game->flag.f > 1 || game->flag.c > 1)
    {
        print_err("Invalide Element !",game);
    }
}

void make_map_rectangular(t_game *game)
{
    int i;
    int j;
    int len;
    char *new_line;

    i = 0;
    while (i < game->map.height)
    {
        len = ft_strlen(game->map.grid[i]);
        // If the line is shorter than the max width, we need to pad it
        if (len < game->map.width)
        {
            // Allocate new string (width + 1 for null terminator)
            new_line = malloc(sizeof(char) * (game->map.width + 1));
            if (!new_line)
                exit(1); // Handle error properly

            // Copy the existing map data
            j = 0;
            while (j < len)
            {
                new_line[j] = game->map.grid[i][j];
                j++;
            }
            // Fill the rest with spaces
            while (j < game->map.width)
            {
                new_line[j] = ' '; 
                j++;
            }
            new_line[j] = '\0'; // Null terminate

            // Free the old short line and replace it with the new long line
            free(game->map.grid[i]);
            game->map.grid[i] = new_line;
        }
        i++;
    }
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
	make_map_rectangular(game); // used here
    search_player(game);
    flag_check(game);
    return (0);
}