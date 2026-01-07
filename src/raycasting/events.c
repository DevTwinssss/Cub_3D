/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:50:38 by hind              #+#    #+#             */
/*   Updated: 2026/01/07 20:50:07 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_press(int keycode, t_game *game)
{
	if (keycode == N)
		game->player.move_up = 1;
	if (keycode == S)
		game->player.move_down = 1;
	if (keycode == W)
		game->player.move_left = 1;
	if (keycode == E)
		game->player.move_right = 1;
	if (keycode == LEFT_ROTATE)
		game->player.left_rot = 1;
	if (keycode == RIGHT_ROTATE)
		game->player.right_rot = 1;
	if (keycode == ESC)
	{
		cleanup_game(game);
		exit(0);
	}
	return (0);
}

int	release(int keycode, t_game *game)
{
	if (keycode == N)
		game->player.move_up = 0;
	if (keycode == S)
		game->player.move_down = 0;
	if (keycode == W)
		game->player.move_left = 0;
	if (keycode == E)
		game->player.move_right = 0;
	if (keycode == LEFT_ROTATE)
		game->player.left_rot = 0;
	if (keycode == RIGHT_ROTATE)
		game->player.right_rot = 0;
	return (0);
}

int	mouse_move(int x, int y, t_game *game)
{
	int	diff_center_x;

	(void)y;
	diff_center_x = x - (SCREENWIDTH / 2);
	game->player.player_angle += diff_center_x * 0.0001;
	game->player.dir_x = cos(game->player.player_angle);
	game->player.dir_y = sin(game->player.player_angle);
	mlx_mouse_move(game->mlx, game->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	return (0);
}

int	press(t_game *game)
{
	up_down(game);
	left_right(game);
	rotation(game);
	render_background(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
