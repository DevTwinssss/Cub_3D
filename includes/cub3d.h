#ifndef CUB3D_H
#define CUB3D_H

// +++++++++++++++

#define tile_size 32
#define mapWidth 24
#define mapHeight 21
#define playersize 7
#define N 119
#define S 115
#define E 100
#define W 97
#define left_rotate 65361
#define right_rotate 65363
#define speed 0.2
#define PI 3.14159265358979323846
#define FOV 60*(PI/180)
#define screenWidth (mapWidth * tile_size)
#define screenHeight (mapHeight * tile_size)

extern int worldMap[mapHeight][mapWidth];


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include <X11/keysym.h>

typedef struct s_player {
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
	//+++++++++
	int move_up;
    int move_down;
    int move_left;
    int move_right;
    int left_rot;
    int right_rot;

	double player_angle;

} t_player;

typedef struct s_config {
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
	// +++++++++++++++
	void *img;
	int *data;


	
} t_game;

void	draw_map(int *data);
int 	is_press(int keycode, t_game *game);
int		release(int keycode, t_game *game);
int		press(t_game *game);
void	draw_square(t_game *game, int x, int y, int size, int color);
void	draw_line(void *mlx, void *win, int x0, int y0, double dir_x, double dir_y, int length, int color);
void	cast_rays(t_game *game);













#endif