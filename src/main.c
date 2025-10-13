#include "../includes/cub3d.h"

void	draw_map(int *data);

#define tile_size 32
#define mapWidth 24
#define mapHeight 21
#define playersize 10
#define N 119
#define S 115
#define E 100
#define W 97
#define speed 0.2


#define screenWidth (mapWidth * tile_size)
#define screenHeight (mapHeight * tile_size)


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

void    draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        mlx_pixel_put(mlx, win, x0, y0, color); // draw pixel

        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

int derections(int keycode, t_game *game)
{
	if(keycode == 65362) // (0,-1)
	{
		game->player.dir_x = (game->player.x + 0) * 50;
		game->player.dir_x = (game->player.y - 1) * 50;
	}
	if(keycode == 65364) // (0,1)
	{
		game->player.dir_x = (game->player.x + 0) * 50;
		game->player.dir_x = (game->player.y + 1) * 50;
	}
	if(keycode == 65363) // (1,0)
	{
		game->player.dir_x = (game->player.x + 1) * 50;
		game->player.dir_x = (game->player.y + 0) * 50;
	}
	if(keycode == 65361) // (-1,0)
	{
		game->player.dir_x = (game->player.x - 1) * 50;
		game->player.dir_x = (game->player.y + 0) * 50;
	}
	return (0);

}

int is_press(int keycode, t_game *game)
{

	if (keycode == N) //UP
		game->player.move_up = 1, printf("in pres 1\n");
	if (keycode == S) //down
		game->player.move_down = 1, printf("in pres 2\n");
	if (keycode == W) // left
		game->player.move_left = 1, printf("in pres 3\n");
	if (keycode == E) // right
		game->player.move_right = 1, printf("in pres 4\n");
	if (keycode == 65307) // esc
		exit(0);

	return(0);
}

int release(int keycode, t_game *game)
{
	if (keycode == N) //UP
		game->player.move_up = 0, printf("releaaas 1\n");
	if (keycode == S) //down
		game->player.move_down = 0, printf("releaaas 2\n");
	if (keycode == W) // left
		game->player.move_left = 0, printf("releaaas 3\n");
	if (keycode == E) // right
		game->player.move_right = 0, printf("releaaas 4\n");

	return(0);
}


int	press(t_game *game)
{
	int x, y;
	// derections(keycode, game);
	if (game->player.move_up == 1) //UP
	{
		printf("m up\n");
		x = (int) (game->player.x + 0 * speed) / tile_size;
		y = (int) (game->player.y - 1 * speed) / tile_size;

		if(worldMap[y][x] == 0)
		{
			game->player.x = game->player.x + 0 * speed;
			game->player.y = game->player.y - 1 * speed;
		}

	}
	if (game->player.move_down) //down
	{
		printf("m down\n");

		x = (int) (game->player.x + 0 * speed) / tile_size;
		y = (int) (game->player.y + 1 * speed) / tile_size;
	
		if(worldMap[y][x] == 0)
		{
			game->player.x = game->player.x + 0 * speed ;
			game->player.y = game->player.y + 1 * speed ;
		}

	}	
	if (game->player.move_left) // left
	{
		printf("m left\n");

		x = (int) (game->player.x - 1 * speed) / tile_size;
		y = (int) (game->player.y + 0 * speed) / tile_size;
	
		if(worldMap[y][x] == 0)
		{
			game->player.x = game->player.x - 1 * speed ; 
			game->player.y = game->player.y + 0 * speed ;
		}

	}	
	if (game->player.move_right) // right
	{
		printf("m right\n");

		x = (int) (game->player.x + 1 * speed) / tile_size;
		y = (int) (game->player.y + 0 * speed) / tile_size;
	
		if(worldMap[y][x] == 0)
		{
			game->player.x = game->player.x + 1 * speed ; 
			game->player.y = game->player.y + 0 * speed ;
		}
	}	
	// if (keycode == 65307)
	// {
	// 	exit(-1);
	// // 	ft_putstr_fd("You Exit The GAME\n", 1);
	// // 	close_game(game);
	// }

	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	draw_square(game, game->player.x, game->player.y, playersize,  0x1026a3);
	
	draw_line(game->mlx, game->win, game->player.x, game->player.y,
		game->player.dir_x, game->player.dir_y, 0x1eff00);


	return (0);
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

int main()
{
	t_game *game;
	int bit_per_pixel;
	int line_len;
	int endian;

	game = (t_game*) malloc(sizeof(t_game));

	// initt
	game->player.x = (screenWidth)/2 + 10;
	game->player.y = (screenHeight)/2 - 6;
	game->player.move_up = 0;
    game->player.move_down = 0;
    game->player.move_left = 0;
    game->player.move_right = 0;

	// game->player.dir_x = 0;
	// game->player.dir_y = 1;

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "cub3d");
	game->img = mlx_new_image(game->mlx, screenWidth, screenHeight);
	game->data = (int *) mlx_get_data_addr(game->img, &bit_per_pixel, &line_len, &endian);


	draw_map(game->data);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	draw_square(game, game->player.x , game->player.y, playersize, 0x1026a3);
	
	mlx_hook(game->win, 2, 1L<<0 , is_press, game); // press in key  
	mlx_hook(game->win, 3, 1L<<1 , release, game); // up the key
	mlx_loop_hook(game->mlx, press, game); // loop to continue 

	// mlx_key_hook(game->win, press, game);
	
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
 
collision detection
rotation
and raycasting
- Cast rays from a player’s position.
- Detect wall intersections.
- Compute distances correctly (without distortion).
- Project walls on screen in 3D.


*/