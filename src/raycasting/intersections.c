/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:01:58 by hind              #+#    #+#             */
/*   Updated: 2026/01/07 17:19:13 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

t_point	check_next_inters(t_game *game, t_point firstInte, double xa, double ya)
{
	t_point	next_hit;

	next_hit.x = firstInte.x;
	next_hit.y = firstInte.y;
	while (next_hit.x >= 0 && next_hit.x < (game->map.width * tile_size) && \
		next_hit.y >= 0 && next_hit.y < (game->map.height * tile_size) && \
		game->map.grid[(int)(next_hit.y / tile_size)] \
						[(int)(next_hit.x / tile_size)] != '1')
	{
		next_hit.x += xa;
		next_hit.y += ya;
	}
	return (next_hit);
}

t_point	vertical_intersection(t_game *game, double ray_angle)
{
	t_point	first_inters;

	double (xa), (ya);
	first_inters = first_ver_intersection(game, ray_angle);
	if (ray_angle < (270 * (PI / 180)) && ray_angle > (90 * (PI / 180)))
		xa = -tile_size;
	else
		xa = tile_size;
	ya = xa * tan(ray_angle);
	return (check_next_inters(game, first_inters, xa, ya));
}

t_point	horizontal_intersection(t_game *game, double ray_angle)
{
	t_point	first_inters;

	double (xa), (ya);
	first_inters = first_hori_intersection(game, ray_angle);
	if (ray_angle > 0 && ray_angle < (180 * (PI / 180)))
		ya = tile_size;
	else
		ya = -tile_size;
	xa = ya / tan(ray_angle);
	return (check_next_inters(game, first_inters, xa, ya));
}
