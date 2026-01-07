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
    if (!game->config.floor_color) // should check -1 not 0 (0 is black)
        print_err("Missing F color", game);
    if (!game->config.ceiling_color)  // should check -1 not 0 (0 is black)
        print_err("Missing C color", game);
}

void remove_newline(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '\n' || str[i] == '\r')
        {
            str[i] = '\0';
            return;
        }
        i++;
    }
}

int check_config(char *line, t_game *game)
{
    if(ft_strncmp(line,"NO ",3) == 0)
	{
        game->config.no_path = ft_strdup(line + 3);
		remove_newline(game->config.no_path);
	}
    else if(ft_strncmp(line,"SO ",3) == 0)
	{
		game->config.so_path = ft_strdup(line + 3);
		remove_newline(game->config.so_path);
	}
    else if(ft_strncmp(line,"WE ",3) == 0)
	{
        game->config.we_path = ft_strdup(line + 3);    
		remove_newline(game->config.we_path);
	}
    else if(ft_strncmp(line,"EA ",3) == 0)
	{
		game->config.ea_path = ft_strdup(line + 3);
		remove_newline(game->config.ea_path);
	}
    else if (line[0] == 'F')
        game->config.floor_color = parse_color(line + 2 ,game);
    else if (line[0] == 'C')
        game->config.ceiling_color = parse_color(line + 2,game);
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
        game->flag.no++;
    else if(ft_strncmp(line, "SO ", 3) == 0)
        game->flag.so++;
    else if(ft_strncmp(line, "EA ", 3) == 0)
        game->flag.ea++;
    else if(ft_strncmp(line, "WE ", 3) == 0)
        game->flag.we++;
    else if(ft_strncmp(line, "F ", 2) == 0)
        game->flag.f++;
    else if(ft_strncmp(line, "C ", 2) == 0)
        game->flag.c++;
    else
        return(1);
    return(0);
}


