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
#define left_rotate 65361
#define right_rotate 65363
#define speed 0.2
#define PI 3.14159265358979323846

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

// void draw_line(void *mlx, void *win, int x0, int y0, double x1, double y1, int length, int color)
// {
// 	// // direction based on angle
// 	// double dx = cos(angle);
// 	// double dy = sin(angle);

// 	// loop to draw only "length" pixels
// 	for (int i = 0; i < length; i++)
// 	{
// 		int x = x0 + (int)(x1 * i);
// 		int y = y0 + (int)(y1 * i);
// 		mlx_pixel_put(mlx, win, x, y, color);
// 	}
// }
void draw_line(void *mlx, void *win, int x0, int y0, double dir_x, double dir_y, int length, int color)
{
    for (int i = 0; i < length; i++)
    {
        int x = x0 + (int)(dir_x * i);
        int y = y0 + (int)(dir_y * i);
        mlx_pixel_put(mlx, win, x, y, color);
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
	if(keycode == 65363) // (1,0) right
	{
		game->player.dir_x = (game->player.x + 1) * 50;
		game->player.dir_x = (game->player.y + 0) * 50;
	}
	if(keycode == 65361) // (-1,0) left
	{
		game->player.dir_x = (game->player.x - 1) * 50;
		game->player.dir_x = (game->player.y + 0) * 50;
	}
	return (0);

}

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
		exit(0);

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

	if (game->player.move_up == 1) //UP
	{
		x = game->player.x + cos(game->player.player_angle) * speed;
		y = game->player.y + sin(game->player.player_angle) * speed;

		mapx = (int) x / tile_size;
		mapy = (int) y / tile_size;

		if(worldMap[(int)game->player.y / tile_size][mapx] == 0)
			game->player.x = x;
		
		if(worldMap[mapy][(int)game->player.x / tile_size] == 0)
			game->player.y = y;
		

	}
	if (game->player.move_down) //down
	{
		x = game->player.x - cos(game->player.player_angle) * speed;
		y = game->player.y - sin(game->player.player_angle) * speed;
	
		mapx = (int) x / tile_size;
		mapy = (int) y / tile_size;

		if(worldMap[(int)game->player.y / tile_size][mapx] == 0)
			game->player.x = x ;
		
		if(worldMap[mapy][(int)game->player.x / tile_size] == 0)
			game->player.y = y ;

	}	
	if (game->player.move_left) // left
	{
		x = game->player.x + sin(game->player.player_angle) * speed;
		y = game->player.y - cos(game->player.player_angle) * speed;
	
		mapx = (int) x / tile_size;
		mapy = (int) y / tile_size;

		if(worldMap[(int)game->player.y / tile_size][mapx] == 0)
			game->player.x = x ; 
		if(worldMap[mapy][(int)game->player.x / tile_size] == 0)
			game->player.y = y ;

	}	
	if (game->player.move_right) // right
	{
		x = game->player.x - sin(game->player.player_angle) * speed;
		y = game->player.y + cos(game->player.player_angle) * speed;
	
		mapx = (int) x / tile_size;
		mapy = (int) y / tile_size;

		if(worldMap[(int)game->player.y / tile_size][mapx] == 0)
			game->player.x = x ; 
		if(worldMap[mapy][(int)game->player.x / tile_size] == 0)
			game->player.y = y ;
		
	}
	if(game->player.left_rot)
	{
		game->player.player_angle -= 0.1 * (PI / 180);
		game->player.dir_x =  cos(game->player.player_angle);
		game->player.dir_y =  sin(game->player.player_angle);
	}
	if(game->player.right_rot)
	{
		game->player.player_angle += 0.1 * (PI / 180);
		game->player.dir_x =  cos(game->player.player_angle);
		game->player.dir_y =  sin(game->player.player_angle);
	}

	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	draw_square(game, game->player.x, game->player.y, playersize,  0x1026a3);
	draw_line(game->mlx, game->win, game->player.x, game->player.y,
		game->player.dir_x, game->player.dir_y, 500, 0x1eff00);


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
	draw_line(game->mlx, game->win, game->player.x, game->player.y,
		game->player.dir_x, game->player.dir_y, 500, 0x1eff00);

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

rotation
and raycasting
- Cast rays from a player’s position.
- Detect wall intersections.
- Compute distances correctly (without distortion).
- Project walls on screen in 3D.


*/