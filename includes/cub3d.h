/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:33:01 by hind              #+#    #+#             */
/*   Updated: 2026/01/08 01:37:12 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include "../get_next_line/get_next_line.h"

# include <mlx.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <X11/keysym.h>

# define N 119
# define S 115
# define E 100
# define W 97
# define ESC 65307
# define LEFT_ROTATE 65361
# define RIGHT_ROTATE 65363
# define SPEED 3
# define PI 3.14159265358979323846
# define FOV 1.04719755 // 60 degrees in radians (60 * (PI/180))
# define SCREENWIDTH 1280
# define SCREENHEIGHT 720
# define TILE_SIZE 64 

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		move_up;
	int		move_down;
	int		move_left;
	int		move_right;
	int		left_rot;
	int		right_rot;
	double	distance;
	double	player_angle;

}	t_player;

typedef struct s_point
{
	double	x;
	double	y;

}	t_point;

typedef struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;

}	t_config;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;

}	t_map;

typedef struct s_texture
{
	void	*img;
	int		*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;

}	t_texture;

typedef struct s_wall
{
	double	line_height;
	int		start;
	int		end;

}	t_wall;

typedef struct s_conf_dup
{
	int	so;
	int	no;
	int	ea;
	int	we;
	int	f;
	int	c;

}	t_cd;

typedef struct s_game
{
	t_config	config;
	t_map		map;
	t_player	player;
	t_cd		flag;
	t_wall		wall;
	t_texture	textures[4];
	void		*mlx;
	void		*win;
	void		*img;
	int			*data;

}	t_game;

//utils
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *str);
char	**ft_split(char const *s, char c);

//parsing 
int		parsing(char *str, t_game *game);
int		parse_map(int fd, t_game *game);
int		valide_name(char *str);
int		open_file(char *str);
int		check_config(char *line, t_game *game);
void	add_line_map(char *line, t_game *game);
int		is_map_line(char *line);
void	check_map(t_game *game);
int		is_config_line(char *line, t_game *game);
char	*ft_strdup(const char *s);
void	validate_config(t_game *game);
int		parse_color(char *str, t_game *game);
void	search_player(t_game *game);
void	make_map_rectangular(t_game *game);

// Garbage collector functions
void	init_game(t_game *game);
void	free_config(t_config *config);
void	free_map(t_map *map);
void	cleanup_game(t_game *game);
void	print_err(char *err, t_game *game);

// raycasting
int		is_press(int keycode, t_game *game);
int		release(int keycode, t_game *game);
int		mouse_move(int x, int y, t_game *game);
int		press(t_game *game);
void	cast_rays(t_game *game);
t_point	horizontal_intersection(t_game *game, double ray_angle);
t_point	vertical_intersection(t_game *game, double ray_angle);
double	distance(double x1, double y1, double x2, double y2);
double	normalize_angle(double angle);

void	init_graphics(t_game *game);
void	render_background(t_game *game);
void	load_textures(t_game *game);

void	rotation(t_game *game);
void	up_down(t_game *game);
void	left_right(t_game *game);
t_point	handle_collision(double x, double y, t_game *game);
void	move(double x, double y, t_game *game);

t_point	first_ver_intersection(t_game *game, double ray_angle);
t_point	first_hori_intersection(t_game *game, double ray_angle);

void	draw_ver_lines(t_texture *tex, t_game *game, int texture_x, int i);
void	render_background(t_game *game);
int		get_pixel_color(t_texture *tex, int tex_x, int tex_y);

#endif