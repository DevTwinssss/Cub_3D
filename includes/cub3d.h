#ifndef CUB3D_H
#define CUB3D_H

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






//parsing 
void pars_map();








#endif

