#ifndef CUB3D_H
#define CUB3D_H

// +++++++++++++++
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

#endif