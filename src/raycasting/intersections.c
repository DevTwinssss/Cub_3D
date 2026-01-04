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
	t_point first_inters;
	double  next_x, next_y, xa, ya;

	ray_angle = normalize_angle(ray_angle);
	first_inters = first_ver_intersection(game, ray_angle);
	if(ray_angle < (270 * (PI / 180)) && ray_angle > (90 * (PI / 180))) // looking left // calculate the XA and YA
		xa = -tile_size;
	else 
		xa = tile_size;
	ya = xa * tan(ray_angle);
	next_x = first_inters.x;// find other intersections
	next_y = first_inters.y;
	while (next_x >= 0 && next_x < (game->map.width * tile_size) &&
		next_y >= 0 && next_y < (game->map.height * tile_size) &&
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
	t_point first_inters;
	double  next_x, next_y, xa, ya;

	ray_angle = normalize_angle(ray_angle);
	first_inters = first_hori_intersection(game, ray_angle);
	if(ray_angle > 0 && ray_angle < (180 * (PI / 180))) // calculate the XA and YA	// looking down
		ya = tile_size;
	else 
		ya = -tile_size;
	xa = ya / tan(ray_angle);
	next_x = first_inters.x;// find other intersections
	next_y = first_inters.y;
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
