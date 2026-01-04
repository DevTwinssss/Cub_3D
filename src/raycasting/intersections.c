#include "../../includes/cub3d.h"



/*
we use the normalize angle to keep th angle between [0 - 2π]
to give tan cos sin the correcte directions, and direction checks consistent
*/
double normalize_angle(double angle)
{
    angle = fmod(angle, 2 * PI); // remainder = angle mod 2π 
    if (angle < 0) // handle negative values
        angle += 2 * PI;
    return angle;
}


double distance(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

t_point vertical_intersection(t_game *game, double ray_angle)
{
	t_point hit;
	double  first_x, first_y, next_x, next_y, xa, ya;

	ray_angle = normalize_angle(ray_angle);

	// find first intersection (y,x)
	if(ray_angle < (270 * (PI / 180)) && ray_angle > (90 * (PI / 180))) // looking left
		first_x = floor(game->player.x / tile_size) * tile_size - 0.01; // find y-coordinate of the top border of that row
	else // looking right
		first_x = floor(game->player.x / tile_size) * tile_size + tile_size; // find y-coordinate of the top border of that row
	first_y = tan(ray_angle) * (first_x - game->player.x) + game->player.y;


	// calculate the XA and YA
	if(ray_angle < (270 * (PI / 180)) && ray_angle > (90 * (PI / 180))) // looking left
		xa = -tile_size;
	else 
		xa = tile_size;
	ya = xa * tan(ray_angle);

	// find other intersections
	next_x = first_x;
	next_y = first_y;

	// printf("y = %d, x = %d\n", (int)(next_y / tile_size), (int)(next_x / tile_size));
	while (next_x >= 0 && next_x < game->map.width * tile_size &&
		next_y >= 0 && next_y < game->map.height * tile_size &&
		game->map.grid[(int)(next_y / tile_size)][(int)(next_x / tile_size)] != '1')
	{
		next_x += xa;
		next_y += ya;
	}

	hit.x = next_x;
	hit.y = next_y;

	return(hit);
}

t_point horizontal_intersection(t_game *game, double ray_angle)
{
	t_point hit;
	double  first_x, first_y, next_x, next_y, xa, ya;

	ray_angle = normalize_angle(ray_angle);
	if(ray_angle > 0 && ray_angle < (180 * (PI / 180)))	// find first intersection (y,x)	// looking down 
		first_y = floor(game->player.y / tile_size) * tile_size + tile_size; // find y-coordinate of the top border of that row
	else // looking up
		first_y = floor(game->player.y / tile_size) * tile_size - 0.01; // find y-coordinate of the top border of that row
	first_x = (first_y - game->player.y) / tan(ray_angle) + game->player.x;
	if(ray_angle > 0 && ray_angle < (180 * (PI / 180))) // calculate the XA and YA	// looking down
		ya = tile_size;
	else 
		ya = -tile_size;
	xa = ya / tan(ray_angle);
	next_x = first_x; // find other intersections
	next_y = first_y;
    while (next_x >= 0 && next_x < game->map.width * tile_size &&
		next_y >= 0 && next_y < game->map.height * tile_size &&
		game->map.grid[(int)(next_y / tile_size)][(int)(next_x / tile_size)] != '1')
	{
		next_x += xa;
		next_y += ya;
	}
	hit.x = next_x;
	hit.y = next_y;
	return(hit);
}
