/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:20:09 by hind              #+#    #+#             */
/*   Updated: 2026/01/07 17:39:55 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_point	handle_collision(double x, double y, t_game *game)
{
	t_point	map;
	int		collision;

	collision = 20;
	if (x > game->player.x)
		map.x = (int)(x + collision) / TILE_SIZE ;
	else
		map.x = (int)(x - collision) / TILE_SIZE ;
	if (y > game->player.y)
		map.y = (int)(y + collision) / TILE_SIZE ;
	else
		map.y = (int)(y - collision) / TILE_SIZE ;
	return (map);
}

void	move(double x, double y, t_game *game)
{
	t_point	check;
	int		mapx;
	int		mapy;

	check = handle_collision(x, y, game);
	mapx = (int) check.x;
	mapy = (int) check.y;
	if (mapx < 0 || mapy < 0)
		return ;
	if (game->map.grid[(int)game->player.y / TILE_SIZE][mapx] != '1')
		game->player.x = x ;
	if (game->map.grid[mapy][(int)game->player.x / TILE_SIZE] != '1')
		game->player.y = y;
}

void	rotation(t_game *game)
{
	if (game->player.left_rot)
	{
		game->player.player_angle -= SPEED * (PI / 180);
		game->player.dir_x = cos(game->player.player_angle);
		game->player.dir_y = sin(game->player.player_angle);
	}
	if (game->player.right_rot)
	{
		game->player.player_angle += SPEED * (PI / 180);
		game->player.dir_x = cos(game->player.player_angle);
		game->player.dir_y = sin(game->player.player_angle);
	}
}

void	up_down(t_game *game)
{
	double	x;
	double	y;

	if (game->player.move_up)
	{
		x = game->player.x + cos(game->player.player_angle) * SPEED;
		y = game->player.y + sin(game->player.player_angle) * SPEED;
		move(x, y, game);
	}
	if (game->player.move_down)
	{
		x = game->player.x - cos(game->player.player_angle) * SPEED;
		y = game->player.y - sin(game->player.player_angle) * SPEED;
		move(x, y, game);
	}
}

void	left_right(t_game *game)
{
	double	x;
	double	y;

	if (game->player.move_left)
	{
		x = game->player.x + sin(game->player.player_angle) * SPEED;
		y = game->player.y - cos(game->player.player_angle) * SPEED;
		move(x, y, game);
	}
	if (game->player.move_right)
	{
		x = game->player.x - sin(game->player.player_angle) * SPEED;
		y = game->player.y + cos(game->player.player_angle) * SPEED;
		move(x, y, game);
	}
}
