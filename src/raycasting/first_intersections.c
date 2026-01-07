/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:52:32 by hind              #+#    #+#             */
/*   Updated: 2026/01/07 16:55:02 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_point	first_ver_intersection(t_game *game, double ray_angle)
{
	t_point	first;

	if (ray_angle < (270 * (PI / 180)) && ray_angle > (90 * (PI / 180)))
		first.x = floor(game->player.x / tile_size) * tile_size - 0.0001;
	else
		first.x = floor(game->player.x / tile_size) * tile_size + tile_size;
	first.y = tan(ray_angle) * (first.x - game->player.x) + game->player.y;
	return (first);
}

t_point	first_hori_intersection(t_game *game, double ray_angle)
{
	t_point	first;

	if (ray_angle > 0 && ray_angle < (180 * (PI / 180)))
		first.y = floor(game->player.y / tile_size) * tile_size + tile_size;
	else
		first.y = floor(game->player.y / tile_size) * tile_size - 0.0001;
	first.x = (first.y - game->player.y) / tan(ray_angle) + game->player.x;
	return (first);
}
