/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:13:11 by hind              #+#    #+#             */
/*   Updated: 2026/01/10 22:35:20 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_pixel_color(t_texture *tex, int tex_x, int tex_y)
{
	if (tex_x < 0 || tex_x >= tex->width || tex_y < 0 || tex_y >= tex->height)
		return (0);
	return (tex->addr[tex_y * tex->width + tex_x]);
}

t_texture	*select_texture(t_game *game, double ray_angle, int is_horizontal)
{
	t_texture	*right_texture;

	if (is_horizontal)
	{
		if (ray_angle > 0 && ray_angle < PI)
			right_texture = &game->textures[0];
		else
			right_texture = &game->textures[1];
	}
	else
	{
		if (ray_angle < (PI / 2) || ray_angle > (3 * PI / 2))
			right_texture = &game->textures[2];
		else
			right_texture = &game->textures[3];
	}
	return (right_texture);
}

int	get_texture_x(t_point h_hit, t_point v_hit, int is_horiz, t_texture *tex)
{
	double	hit_wall_position;
	int		texture_x;

	if (is_horiz)
		hit_wall_position = h_hit.x / TILE_SIZE;
	else
		hit_wall_position = v_hit.y / TILE_SIZE;
	hit_wall_position -= floor(hit_wall_position);
	texture_x = (int)(hit_wall_position * (double)tex->width);
	return (texture_x);
}

int	calc_player_dis(t_game *game, t_point h_hit, t_point v_hit, double rayAngle)
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
	game->player.distance *= cos(rayAngle - game->player.player_angle);
	return (is_horizontal);
}

void	cast_rays(t_game *game)
{
	t_texture	*tex;
	t_point		h_hit;
	t_point		v_hit;
	double		ray_angle;

	int (is_horizontal), (i), (texture_x);
	i = 0;
	ray_angle = game->player.player_angle - (FOV / 2);
	while (i < SCREENWIDTH)
	{
		ray_angle = normalize_angle(ray_angle);
		h_hit = horizontal_intersection(game, ray_angle);
		v_hit = vertical_intersection(game, ray_angle);
		is_horizontal = calc_player_dis(game, h_hit, v_hit, ray_angle);
		game->wall.line_height = (TILE_SIZE / game->player.distance)
			* ((SCREENWIDTH / 2) / tan(FOV / 2));
		game->wall.start = (SCREENHEIGHT / 2) - (game->wall.line_height / 2);
		game->wall.end = (SCREENHEIGHT / 2) + (game->wall.line_height / 2);
		tex = select_texture(game, ray_angle, is_horizontal);
		texture_x = get_texture_x(h_hit, v_hit, is_horizontal, tex);
		draw_ver_lines(tex, game, texture_x, i);
		i++;
		ray_angle += FOV / SCREENWIDTH;
	}
}
