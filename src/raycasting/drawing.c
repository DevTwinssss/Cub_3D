#include "../../includes/cub3d.h"

/* calculates the memory address of the pixel at (x, y) */
int get_pixel_color(t_texture *tex, int tex_x, int tex_y)
{
	if (tex_x < 0 || tex_x >= tex->width || tex_y < 0 || tex_y >= tex->height)
		return (0);
	return (tex->addr[tex_y * tex->width + tex_x]);
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

t_texture	*select_texture(t_game *game, double	ray_angle, int is_horizontal)
{
	t_texture	*right_texture;

	if (is_horizontal)
	{
		// If facing DOWN (Angle 0 to PI) -> Hit North Face -> Use NO Texture
		// If facing UP (Angle PI to 2PI) -> Hit South Face -> Use SO Texture
		if (ray_angle > 0 && ray_angle < PI)
			right_texture = &game->textures[0]; // NO
		else
			right_texture = &game->textures[1]; // SO
	}
	else
	{
		// If facing RIGHT (Angle < PI/2 or > 3PI/2) -> Hit West Face -> Use WE Texture
		// If facing LEFT (Angle PI/2 to 3PI/2) -> Hit East Face -> Use EA Texture
		if (ray_angle < (PI / 2) || ray_angle > (3 * PI / 2))
			right_texture = &game->textures[2]; // WE
		else
			right_texture = &game->textures[3]; // EA
	}

	return (right_texture);
}

int get_texture_x(t_point h_hit, t_point  v_hit, int is_horizontal, t_texture *tex)
{
	double	hit_wall_position;
	int		texture_x;

	// ---  4: CALCULATE TEXTURE X (hit_wall_position) --- Find the x or y position of the wall we hit
	if (is_horizontal)
		hit_wall_position = h_hit.x / tile_size; // ex: 2050.5 / 64 = [ 32.039 ]
	else
		hit_wall_position = v_hit.y / tile_size;

	hit_wall_position -= floor(hit_wall_position); // Get only the decimal part (0.0 to 1.0) [we care about where exactly we hit this wall (start, end, middle ...)]

	// Convert decimal to pixel X on texture (0 to 63)
	// get the specific column of pixels from the texture image (ex: 0.5 * 64 = 32) -> column 32
	texture_x = (int)(hit_wall_position * (double)tex->width);

	return(texture_x);
}

int	calc_player_dis(t_game *game, t_point h_hit, t_point v_hit, double	ray_angle)
{
	int			is_horizontal;
	double		dist_h;
	double		dist_v;

	dist_h = distance(game->player.x, game->player.y, h_hit.x, h_hit.y);
	dist_v = distance(game->player.x, game->player.y, v_hit.x, v_hit.y);

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

	// Fix fisheye
	game->player.distance *= cos(ray_angle - game->player.player_angle); 

	return (is_horizontal);
}

// void draw_ver_lines(t_texture	*tex, t_game *game, int texture_x_pos, int i)
// {
	
// 	// ---  5: DRAW THE STRIP (vertical lines) ---
// 	// Calculate how much to increase texture Y per screen pixel (moving down )
// 	double step = tex->height / game->wall.line_height;
	
// 	// Calculate initial texture position (coordinate on the Texture) (Where exactly does the texture start matching the wall)
// 	double texPos = (game->wall.start - screenHeight / 2 + game->wall.line_height / 2) * step;
// 	// is can be [texpos = start * step]

// 	int y = game->wall.start;
// 	if (y < 0) // Handle case where line is taller than screen (start = -100)
// 	{
// 		texPos += step * -y; // How much texture did we skip
// 		y = 0;
// 	}
// 	// Meaning: "Start drawing at the top of the screen (y=0), but begin reading the texture from Pixel 16." (We cut off the top 16 pixels of the texture because they are "above" the ceiling).
	
// 	int draw_end = game->wall.end;
// 	if (draw_end >= screenHeight) 
// 		draw_end = screenHeight;

// 	while (y < draw_end)
// 	{
// 		int teture_y_pos = (int)texPos % tex->height; // 
// 		texPos += step;
		
// 		int color = get_pixel_color(tex, texture_x_pos, teture_y_pos);
		
// 		game->data[y * screenWidth + i] = color;
// 		// tex->addr[y * screenWidth + i] = color; // and put image not pixels 
// 		y++;
// 	}

// }


void draw_ver_lines(t_texture *tex, t_game *game, int texture_x, int i)
{
	double (step), (texture_pos);
	int (texture_y), (color);
	step = tex->height / game->wall.line_height;
	if(game->wall.start < 0)
		game->wall.start = 0;
	texture_pos = (game->wall.start - (screenHeight / 2 - game->wall.line_height / 2)) * step;
	if (game->wall.end >= screenHeight) 
		game->wall.end = screenHeight;
	while (game->wall.start < game->wall.end)
	{
		texture_y = (int)texture_pos % tex->height; // 
		texture_pos += step;
		color = get_pixel_color(tex, texture_x, texture_y);
		game->data[game->wall.start * screenWidth + i] = color;
		game->wall.start++;
	}
}


void cast_rays(t_game *game)
{
	double		ray_angle;
	t_texture	*tex;
	
	t_point (h_hit), (v_hit);
	int (is_horizontal), (i), (texture_x); // 1 if horizontal, 0 if vertical
	i = 0;
	ray_angle = game->player.player_angle - (FOV/2); // Start fov
	while (i < screenWidth)
	{
		ray_angle = normalize_angle(ray_angle); // Keep angle between 0 and 2PI
		h_hit = horizontal_intersection(game, ray_angle); // --- 1: INTERSECTIONS & DISTANCE ---
		v_hit = vertical_intersection(game, ray_angle); // --- 1: INTERSECTIONS & DISTANCE ---
		is_horizontal = calc_player_dis(game, h_hit, v_hit, ray_angle); // get right player distance and return int
		game->wall.line_height = (tile_size / game->player.distance) * ((screenWidth / 2) / tan(FOV / 2)); // ---  3: CALCULATE WALL GEOMETRY ---
		game->wall.start = (screenHeight / 2) - (game->wall.line_height / 2); // ---  3: CALCULATE WALL GEOMETRY ---
		game->wall.end = (screenHeight / 2) + (game->wall.line_height / 2); // ---  3: CALCULATE WALL GEOMETRY ---
		tex = select_texture(game, ray_angle, is_horizontal);
		texture_x = get_texture_x(h_hit, v_hit, is_horizontal, tex);
		draw_ver_lines(tex, game, texture_x, i);
		i++;
		ray_angle += FOV / screenWidth;
	}
}
