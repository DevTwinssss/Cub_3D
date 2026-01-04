#include "../../includes/cub3d.h"

t_point first_ver_intersection(t_game *game, double ray_angle)
{
	t_point  first;

	if(ray_angle < (270 * (PI / 180)) && ray_angle > (90 * (PI / 180))) // looking left
		first.x= floor(game->player.x / tile_size) * tile_size - 0.0001; // find y-coordinate of the top border of that row
	else // looking right
		first.x = floor(game->player.x / tile_size) * tile_size + tile_size; // find y-coordinate of the top border of that row
	first.y = tan(ray_angle) * (first.x - game->player.x) + game->player.y;
	return(first);	
}

t_point first_hori_intersection(t_game *game, double ray_angle)
{
	t_point  first;

	if(ray_angle > 0 && ray_angle < (180 * (PI / 180)))	// find first intersection (y,x)	// looking down 
		first.y = floor(game->player.y / tile_size) * tile_size + tile_size; // find y-coordinate of the top border of that row
	else // looking up
		first.y = floor(game->player.y / tile_size) * tile_size - 0.0001; // find y-coordinate of the top border of that row
	first.x = (first.y - game->player.y) / tan(ray_angle) + game->player.x;
	return(first);
}