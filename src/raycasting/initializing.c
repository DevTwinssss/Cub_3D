#include "../../includes/cub3d.h"


t_game *initialize()
{
	t_game *game;
	int bit_per_pixel;
	int line_len;
	int endian;
	
	game = (t_game*) malloc(sizeof(t_game));
	game->player.player_angle = 180 * (PI / 180);
	game->player.x = (screenWidth)/2;
	game->player.y = (screenHeight)/2;
	game->player.move_up = 0;
	game->player.move_down = 0;
	game->player.move_left = 0;
	game->player.move_right = 0;
	game->player.left_rot = 0;
	game->player.right_rot = 0;
	game->player.distance = 0;
	game->player.dir_x =  cos(game->player.player_angle);
	game->player.dir_y =  sin(game->player.player_angle);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "cub3d");
	game->img = mlx_new_image(game->mlx, screenWidth, screenHeight);
	game->data = (int *) mlx_get_data_addr(game->img, &bit_per_pixel, &line_len, &endian);
	return(game);
}
