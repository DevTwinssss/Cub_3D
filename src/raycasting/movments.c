#include "../../includes/cub3d.h"

t_point handle_collision(double x, double y, t_game *game)
{
	t_point	map;
	int		collision;
 
	collision = 20;
	if(x > game->player.x) // if we move right +COLLISION, if we move left -COLLISION
		map.x = (int) (x + collision) / tile_size ;
	else
		map.x = (int) (x - collision) / tile_size ;
	if (y > game->player.y)
		map.y = (int) (y + collision) / tile_size ;
	else
		map.y = (int) (y - collision) / tile_size ;
	return (map);
}

void move(double x, double y, t_game *game)
{
	t_point check;
	int	mapx;
	int mapy;

	check = handle_collision(x, y, game);
	mapx = (int) check.x;
	mapy = (int) check.y;
	if (mapx < 0 || mapy < 0) // prevent reading invalid memory in array [-1]
		return ;
	if(game->map.grid[(int)game->player.y / tile_size][mapx] != '1')
		game->player.x = x ;
	if(game->map.grid[mapy][(int)game->player.x / tile_size] != '1')
		game->player.y = y;
}

void rotation(t_game *game)
{
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
}

void up_down(t_game *game)
{
	double x;
	double y;

	if (game->player.move_up) //UP
	{
		x = game->player.x + cos(game->player.player_angle) * speed;
		y = game->player.y + sin(game->player.player_angle) * speed;
		move(x, y, game);
	}
	if (game->player.move_down) //down
	{
		x = game->player.x - cos(game->player.player_angle) * speed;
		y = game->player.y - sin(game->player.player_angle) * speed;
		move(x, y, game);
	}
}

void left_right(t_game *game)
{
	double x;
	double y;
	
	if (game->player.move_left) // left
	{
		x = game->player.x + sin(game->player.player_angle) * speed;
		y = game->player.y - cos(game->player.player_angle) * speed;
		move(x, y, game);
	}	
	if (game->player.move_right) // right
	{
		x = game->player.x - sin(game->player.player_angle) * speed;
		y = game->player.y + cos(game->player.player_angle) * speed;
		move(x, y, game);
	}
}