#include "../../includes/cub3d.h"







void draw_square(t_game *game, int x, int y, int size, int color)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
}



void draw_line(void *mlx, void *win, double x0, double y0, double x1, double y1, int color)
{ // DDA algorithem
    double dx = x1 - x0;
    double dy = y1 - y0;
    double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    double x_inc = dx / steps;
    double y_inc = dy / steps;

    double x = x0;
    double y = y0;

    for (int i = 0; i <= steps; i++)
    {
        mlx_pixel_put(mlx, win, (int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
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

	t_point horizontal_hit ;//=  horizontal_intersection(game, game->player.player_angle);
	t_point vertical_hit ;//=  vertical_intersection(game, game->player.player_angle);

	double ray_angle = game->player.player_angle - (FOV/2); // Start fov
	// double ray_angle2 = game->player.player_angle + (FOV/2); // End fov

	// draw_line(game->mlx, game->win, game->player.x, game->player.y,
	// 	horizontal_hit.x, horizontal_hit.y, 0x1eff00);

	int i = 0;
	while (i < screenWidth)
	{
		horizontal_hit = horizontal_intersection(game, ray_angle);
		vertical_hit =  vertical_intersection(game, ray_angle);
		
		double a = distance(game->player.x, game->player.y, horizontal_hit.x, horizontal_hit.y);
		double b =  distance(game->player.x, game->player.y, vertical_hit.x, vertical_hit.y);


		if(a < b) 
		{
			// game->player.x_hit = horizontal_hit.x;
			// game->player.y_hit = horizontal_hit.y;
			game->player.distance = a;
		}
		else 
		{
			// game->player.x_hit = vertical_hit.x;
			// game->player.y_hit = vertical_hit.y;
			game->player.distance = b;
		}

		double line_hight = (tile_size / game->player.distance) * ((screenWidth / 2) / tan(FOV / 2));
		double start = (screenHeight / 2) - (line_hight / 2);
		double end =  (screenHeight / 2) + (line_hight / 2);

		draw_line(game->mlx, game->win, i, start, i, end, 0xff00d4);

		i++;
		ray_angle += FOV/screenWidth;
	}
}


// void cast_rays(t_game *game)
// {
//     double ray_angle = game->player.player_angle - (FOV / 2);
//     double angle_step = FOV / screenWidth;

//     for (int i = 0; i < screenWidth; i++)
//     {
//         t_point horizontal_hit = horizontal_intersection(game, ray_angle);
//         t_point vertical_hit   = vertical_intersection(game, ray_angle);

//         double dist_h = distance(game->player.x, game->player.y, horizontal_hit.x, horizontal_hit.y);
//         double dist_v = distance(game->player.x, game->player.y, vertical_hit.x, vertical_hit.y);

//         if (dist_h < dist_v)
//             game->player.distance = dist_h;
//         else
//             game->player.distance = dist_v;

//         // 🧠 correct fisheye
//         double corrected_distance = game->player.distance * cos(ray_angle - game->player.player_angle);

//         // 📏 projection math
//         double proj_plane = (screenWidth / 2) / tan(FOV / 2);
//         double line_height = (tile_size / corrected_distance) * proj_plane;

//         double start = (screenHeight / 2) - (line_height / 2);
//         double end   = (screenHeight / 2) + (line_height / 2);

//         // 🧱 draw vertical wall slice
//         draw_line(game->mlx, game->win, i, start, i, end, 0xff00d4);

//         ray_angle += angle_step;
//     }
// }
