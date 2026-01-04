#include "../../includes/cub3d.h"

int is_press(int keycode, t_game *game)
{
	if (keycode == N) //UP
		game->player.move_up = 1;
	if (keycode == S) //down
		game->player.move_down = 1;
	if (keycode == W) // left
		game->player.move_left = 1;
	if (keycode == E) // right
		game->player.move_right = 1;
	if(keycode == left_rotate)
		game->player.left_rot = 1;
	if(keycode == right_rotate)
		game->player.right_rot = 1;
	if (keycode == 65307) // esc
	{
		cleanup_game(game);
		exit(0);
	}

	return(0);
}

int release(int keycode, t_game *game)
{
	if (keycode == N) //UP
		game->player.move_up = 0;
	if (keycode == S) //down
		game->player.move_down = 0;
	if (keycode == W) // left
		game->player.move_left = 0;
	if (keycode == E) // right
		game->player.move_right = 0;
	if(keycode == left_rotate)
		game->player.left_rot = 0;
	if(keycode == right_rotate)
		game->player.right_rot = 0;

	return(0);
}

int	press(t_game *game)
{
	double x, y;
	int mapx, mapy;
	// int collision = 10; // distance from wall in pixels

	if (game->player.move_up == 1) //UP
	{
		x = game->player.x + cos(game->player.player_angle) * speed;
		y = game->player.y + sin(game->player.player_angle) * speed;

		mapx = (int) x / tile_size ;
		mapy = (int) y / tile_size ;

		if (mapx < 0 || mapy < 0)
    		return -1 ;
		if(game->map.grid[(int)game->player.y / tile_size][mapx] != '1')
			game->player.x = x;
		
		if(game->map.grid[mapy][(int)game->player.x / tile_size] != '1')
			game->player.y = y;
	}
	if (game->player.move_down) //down
	{
		x = game->player.x - cos(game->player.player_angle) * speed;
		y = game->player.y - sin(game->player.player_angle) * speed;
	
		mapx = (int) x / tile_size ;
		mapy = (int) y / tile_size ;

		if (mapx < 0 || mapy < 0)
    		return -1 ;
		if(game->map.grid[(int)game->player.y / tile_size][mapx] != '1')
			game->player.x = x ;
		
		if(game->map.grid[mapy][(int)game->player.x / tile_size] != '1')
			game->player.y = y ;

	}	
	if (game->player.move_left) // left
	{
		x = game->player.x + sin(game->player.player_angle) * speed;
		y = game->player.y - cos(game->player.player_angle) * speed;
	
		mapx = (int) x / tile_size ;
		mapy = (int) y / tile_size ;

		if (mapx < 0 || mapy < 0)
    		return -1 ;
		if(game->map.grid[(int)game->player.y / tile_size][mapx] != '1')
			game->player.x = x ; 
		if(game->map.grid[mapy][(int)game->player.x / tile_size] != '1')
			game->player.y = y ;

	}	
	if (game->player.move_right) // right
	{
		x = game->player.x - sin(game->player.player_angle) * speed;
		y = game->player.y + cos(game->player.player_angle) * speed;
	
		mapx = (int) x / tile_size ;
		mapy = (int) y / tile_size ;

		if (mapx < 0 || mapy < 0)
    		return -1 ;
		if(game->map.grid[(int)game->player.y / tile_size][mapx] != '1')
			game->player.x = x ; 
		if(game->map.grid[mapy][(int)game->player.x / tile_size] != '1')
			game->player.y = y ;
		
	}
	if(game->player.left_rot)
	{
		game->player.player_angle -= speed * (PI / 180);
		game->player.dir_x =  cos(game->player.player_angle);
		game->player.dir_y =  sin(game->player.player_angle);
	}
	if(game->player.right_rot)
	{
		game->player.player_angle += speed * (PI / 180);
		game->player.dir_x =  cos(game->player.player_angle);
		game->player.dir_y =  sin(game->player.player_angle);
	}

	// mlx_put_image_to_window(game->mlx, game->win, game->textures[0].img, 0, 0);
	render_background(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

	return (0);
}
