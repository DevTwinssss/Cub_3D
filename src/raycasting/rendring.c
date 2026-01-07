/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:50:02 by hind              #+#    #+#             */
/*   Updated: 2026/01/07 16:50:15 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_ver_lines(t_texture *tex, t_game *game, int texture_x, int i)
{
	double (step), (texture_pos);
	int (texture_y), (color);
	step = tex->height / game->wall.line_height;
	if (game->wall.start < 0)
		game->wall.start = 0;
	texture_pos = (game->wall.start - (screenHeight / 2 - \
		game->wall.line_height / 2)) * step;
	if (game->wall.end >= screenHeight)
		game->wall.end = screenHeight;
	while (game->wall.start < game->wall.end)
	{
		texture_y = (int)texture_pos % tex->height;
		texture_pos += step;
		color = get_pixel_color(tex, texture_x, texture_y);
		game->data[game->wall.start * screenWidth + i] = color;
		game->wall.start++;
	}
}

void	render_background(t_game *game)
{
	int	x;
	int	y;
	int	color;

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
