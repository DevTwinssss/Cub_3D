#include "../includes/cub3d.h"

int worldMap[mapHeight][mapWidth]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,5,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


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
	while (next_x >= 0 && next_x < mapWidth * tile_size &&
		next_y >= 0 && next_y < mapHeight * tile_size &&
		worldMap[(int)(next_y / tile_size)][(int)(next_x / tile_size)] != 1)
	{
		next_x += xa;
		next_y += ya;
	}

	hit.x = next_x;
	hit.y = next_y;

	return(hit);
}

// tan(z) = (ay - py) / (ax - px)

t_point horizontal_intersection(t_game *game, double ray_angle)
{
	t_point hit;
	double  first_x, first_y, next_x, next_y, xa, ya;


	ray_angle = normalize_angle(ray_angle);


	// find first intersection (y,x)
	if(ray_angle > 0 && ray_angle < (180 * (PI / 180))) // looking down
		first_y = floor(game->player.y / tile_size) * tile_size + tile_size; // find y-coordinate of the top border of that row
	else // looking up
		first_y = floor(game->player.y / tile_size) * tile_size - 0.01; // find y-coordinate of the top border of that row
	first_x = (first_y - game->player.y) / tan(ray_angle) + game->player.x;


	// calculate the XA and YA
	if(ray_angle > 0 && ray_angle < (180 * (PI / 180))) // looking down
		ya = tile_size;
	else 
		ya = -tile_size;
	xa = ya / tan(ray_angle);

	// find other intersections
	next_x = first_x;
	next_y = first_y;
    while (next_x >= 0 && next_x < mapWidth * tile_size &&
		next_y >= 0 && next_y < mapHeight * tile_size &&
		worldMap[(int)(next_y / tile_size)][(int)(next_x / tile_size)] != 1)
	{
		next_x += xa;
		next_y += ya;
	}

	hit.x = next_x;
	hit.y = next_y;

	return(hit);
}

// ("i will check po [%d][%d]\n", (int)(next_y / tile_size), (int)(next_x / tile_size));

int main()
{
	t_game *game;
	int bit_per_pixel;
	int line_len;
	int endian;

	game = (t_game*) malloc(sizeof(t_game));
	
	// initt
	game->player.player_angle = 290 * (PI / 180);

	game->player.x = (screenWidth)/2 + 10;
	game->player.y = (screenHeight)/2 - 6;
	
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

	// draw
	// draw_map(game->data);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	// draw_square(game, game->player.x , game->player.y, playersize, 0x1026a3);



	// hooks
	mlx_hook(game->win, 2, 1L<<0 , is_press, game); // press in key  
	mlx_hook(game->win, 3, 1L<<1 , release, game); // up the key
	mlx_loop_hook(game->mlx, press, game); // loop to continue 

	
	mlx_loop(game->mlx);
	return(0);
}


/*
- Compute distances correctly (without distortion).
- Project walls on screen in 3D.
*/