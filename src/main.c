#include "../includes/cub3d.h"

int worldMap[mapHeight][mapWidth]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


void draw_square(t_game *game, int x, int y, int size, int color)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
}

void draw_line(void *mlx, void *win, int x0, int y0, double dir_x, double dir_y, int length, int color)
{
    for (int i = 0; i < length; i++)
    {
        int x = x0 + (int)(dir_x * i);
        int y = y0 + (int)(dir_y * i);
        mlx_pixel_put(mlx, win, x, y, color);
    }
}

void	draw_map(int *data)
{
	int (i), (j);
	i = 0;
	while (i < mapHeight)
	{
		j = 0;
		while (j < mapWidth)
		{
			int color;
			if (worldMap[i][j] == 0)
				color = 0xffffff ;
			else 
				color = 0x4a045f;
			
			// fill tile
			for (int a = 0;  a < tile_size - 1;  a++)
			{
				for (int b = 0;  b < tile_size - 1;  b++)
				{	
					int x = j * tile_size + a;
					int y = i * tile_size + b;
					data[y * screenWidth + x] = color;
				}
			}
			j++;
		}
		i++;
	}
}

void cast_rays(t_game *game)
{
	double ray_angel = game->player.player_angle - (FOV/2);

	double ray_angel2 = game->player.player_angle + (FOV/2);

	draw_line(game->mlx, game->win, game->player.x, game->player.y,
		game->player.dir_x, game->player.dir_y, 100, 0x1eff00);

	draw_line(game->mlx, game->win, game->player.x, game->player.y,
			cos(ray_angel), sin(ray_angel), 100,0xff0000);

	draw_line(game->mlx, game->win, game->player.x, game->player.y,
			cos(ray_angel2), sin(ray_angel2), 100, 0x2600ff);

	while (ray_angel < ray_angel2)
	{
		ray_angel += FOV/50;
		draw_line(game->mlx, game->win, game->player.x, game->player.y,
			cos(ray_angel), sin(ray_angel), 100, 0xff00d4);

		/* code */
	}
	

}

int main()
{
	t_game *game;
	int bit_per_pixel;
	int line_len;
	int endian;

	game = (t_game*) malloc(sizeof(t_game));
	
	// initt
	game->player.player_angle = 0 * (PI / 180);

	game->player.x = (screenWidth)/2 + 10;
	game->player.y = (screenHeight)/2 - 6;
	
	game->player.move_up = 0;
    game->player.move_down = 0;
    game->player.move_left = 0;
    game->player.move_right = 0;
	game->player.left_rot = 0;
	game->player.right_rot = 0;

	game->player.dir_x =  cos(game->player.player_angle);
	game->player.dir_y =  sin(game->player.player_angle);

	
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "cub3d");
	game->img = mlx_new_image(game->mlx, screenWidth, screenHeight);
	game->data = (int *) mlx_get_data_addr(game->img, &bit_per_pixel, &line_len, &endian);

	// draw
	draw_map(game->data);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	draw_square(game, game->player.x , game->player.y, playersize, 0x1026a3);



	// hooks
	mlx_hook(game->win, 2, 1L<<0 , is_press, game); // press in key  
	mlx_hook(game->win, 3, 1L<<1 , release, game); // up the key
	mlx_loop_hook(game->mlx, press, game); // loop to continue 

	
	mlx_loop(game->mlx);
	return(0);
}


/*
 -> player position (x.5, y.5)
*/


/*
- draw map ~~~~~~~
- draw player ~~~~~~~
- move player ~~~~~~~
- collision detection basic ~~~~~~
- rotation ~~~~~
- Cast rays from a player’s position. ~~~~~~~

- Detect wall intersections.
- Compute distances correctly (without distortion).
- Project walls on screen in 3D.
*/