#ifndef CUB3D_H
#define CUB3D_H

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "../get_next_line/get_next_line.h"

typedef struct s_player {
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;

typedef struct s_config 
{
    char *no_path;
    char *so_path;
    char *we_path;
    char *ea_path;
    int floor_color;
    int ceiling_color;
} t_config;

typedef struct s_map {
    char **grid;
    int width;
    int height;
} t_map;

typedef struct s_game {
    t_config config;
    t_map map;
    t_player player;
    void *mlx;
    void *win;
} t_game;

//utils
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);




//parsing 
int parsing(char *str,t_game *game);
int parse_map(int fd,t_game *game);
int	valide_name(char *str);
int open_file(char *str);
int check_config(char *line, t_game *game);






#endif

