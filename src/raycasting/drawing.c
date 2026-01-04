#include "../../includes/cub3d.h"

// void draw_square(t_game *game, int x, int y, int size, int color)
// {
//	 for (int i = 0; i < size; i++)
//		 for (int j = 0; j < size; j++)
//			 mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
// }

// void draw_line(t_game *game, double x0, double y0, double x1, double y1, int color)
// { // DDA algorithem
// 	double dx = x1 - x0;
// 	double dy = y1 - y0;
// 	double steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
// 	double x_inc = dx / steps;
// 	double y_inc = dy / steps;

// 	double x = x0;
// 	double y = y0;

// 	for (int i = 0; i <= steps; i++)
// 	{
// 		mlx_pixel_put(game->mlx, game->win, (int)x, (int)y, color);
// 		x += x_inc;
// 		y += y_inc;
// 	}
// }

// void	draw_map(int *data)
// {
// 	int (i), (j);
// 	i = 0;
// 	while (i < mapHeight)
// 	{
// 		j = 0;
// 		while (j < mapWidth)
// 		{
// 			int color;
// 			if (worldMap[i][j] == 0)
// 				color = 0xffffff ;
// 			else 
// 				color = 0x4a045f;
// 			for (int a = 0;  a < tile_size - 1;  a++) // fill tile
// 			{
// 				for (int b = 0;  b < tile_size - 1;  b++)
// 				{	
// 					int x = j * tile_size + a;
// 					int y = i * tile_size + b;
// 					data[y * screenWidth + x] = color;
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

/* calculates the memory address of the pixel at (x, y) */
int get_pixel_color(t_texture *tex, int x, int y)
{
	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	return (tex->addr[y * tex->width + x]);
}

void render_background(t_game *game)
{
	int x;
	int y;
	int color;

	y = 0;
	while (y < screenHeight)
	{
		x = 0;
		if (y < screenHeight / 2)
			color = game->config.ceiling_color;
		else
			color = game->config.floor_color;		
		while (x < screenWidth)
		{
			game->data[y * screenWidth + x] = color;
			x++;
		}
		y++;
	}
}

void cast_rays(t_game *game)
{
	t_point	h_hit, v_hit;
	double	ray_angle = game->player.player_angle - (FOV/2); // Start fov
	double	wallX;

	int	 i = 0;

	t_texture	*tex;
	int			is_horizontal; // 1 if horizontal, 0 if vertical

	while (i < screenWidth)
	{
		ray_angle = normalize_angle(ray_angle); // Keep angle between 0 and 2PI

		// --- 1: INTERSECTIONS & DISTANCE ---
		h_hit = horizontal_intersection(game, ray_angle);
		v_hit = vertical_intersection(game, ray_angle);
		
		double dist_h = distance(game->player.x, game->player.y, h_hit.x, h_hit.y);
		double dist_v = distance(game->player.x, game->player.y, v_hit.x, v_hit.y);

		if (dist_h < dist_v)
		{
			game->player.distance = dist_h;
			is_horizontal = 1;
		}
		else
		{
			game->player.distance = dist_v;
			is_horizontal = 0;
		}

		// ---  2: SELECT TEXTURE (N, S, E, W) ---
		if (is_horizontal)
		{
			// If facing DOWN (Angle 0 to PI) -> Hit North Face -> Use NO Texture
			// If facing UP (Angle PI to 2PI) -> Hit South Face -> Use SO Texture
			if (ray_angle > 0 && ray_angle < PI)
				tex = &game->textures[0]; // NO
			else
				tex = &game->textures[1]; // SO
		}
		else
		{
			// If facing RIGHT (Angle < PI/2 or > 3PI/2) -> Hit West Face -> Use WE Texture
			// If facing LEFT (Angle PI/2 to 3PI/2) -> Hit East Face -> Use EA Texture
			if (ray_angle < (PI / 2) || ray_angle > (3 * PI / 2))
				tex = &game->textures[2]; // WE
			else
				tex = &game->textures[3]; // EA
		}

		// ---  3: CALCULATE WALL GEOMETRY ---
		game->player.distance *= cos(ray_angle - game->player.player_angle); // Fix fisheye
		double line_height = (tile_size / game->player.distance) * ((screenWidth / 2) / tan(FOV / 2));
		int start = (screenHeight / 2) - (line_height / 2);
		int end = (screenHeight / 2) + (line_height / 2);

		// ---  4: CALCULATE TEXTURE X (wallX) --- Translates the position from map to position in texture (which pixel)
		if (is_horizontal)
			wallX = h_hit.x / tile_size;
		else
			wallX = v_hit.y / tile_size;

		wallX -= floor(wallX); // Get only the decimal part (0.0 to 1.0)

		// Convert decimal to pixel X on texture (0 to 63)
		int texX = (int)(wallX * (double)tex->width);

		// if (texX < 0)
		// 	texX = 0;
		// if (texX >= tex->width)
		// 	texX = tex->width - 1;
		// prevent mirroring
		// if ((is_horizontal && ray_angle > 0 && ray_angle < PI) || 
		//	 (!is_horizontal && (ray_angle > PI / 2 && ray_angle < 3 * PI / 2)))
		//	 texX = tex->width - texX - 1;


		// ---  5: DRAW THE STRIP ---

		// Calculate how much to increase texture Y per screen pixel
		double step = 1.0 * tex->height / line_height;
		
		// Calculate initial texture position (Where exactly does the texture start matching the wall)
		double texPos = (start - screenHeight / 2 + line_height / 2) * step;

		int y = start;
		if (y < 0) // Handle case where line is taller than screen (start = -100)
		{
			texPos += step * -y; // How much texture did we skip
			y = 0;
		}
		// Meaning: "Start drawing at the top of the screen (y=0), but begin reading the texture from Pixel 16." (We cut off the top 16 pixels of the texture because they are "above" the ceiling).
		
		int draw_end = end;
		if (draw_end >= screenHeight) 
			draw_end = screenHeight;

		while (y < draw_end)
		{
			int texY = (int)texPos % tex->height; // Mask for safety (assumes 64x64)
			texPos += step;
			
			int color = get_pixel_color(tex, texX, texY);
			
			game->data[y * screenWidth + i] = color;
			// tex->addr[y * screenWidth + i] = color; // and put image not pixels 
			y++;
		}

		i++;
		ray_angle += FOV / screenWidth;
	}
}
