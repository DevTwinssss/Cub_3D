/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:52:35 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/07 16:52:35 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	search_pos(int y, int x, t_game *game)
{
	game->player.x = ((double)x * TILE_SIZE) + (TILE_SIZE / 2.0);
    game->player.y = ((double)y * TILE_SIZE) + (TILE_SIZE / 2.0);

	if (game->map.grid[y][x] == 'N')
		game->player.player_angle = 3 * PI / 2;
	else if (game->map.grid[y][x] == 'S')
		game->player.player_angle = PI / 2;
	else if (game->map.grid[y][x] == 'E')
		game->player.player_angle = 0;
	else if (game->map.grid[y][x] == 'W')
		game->player.player_angle = PI;
}

void	search_player(t_game *game)
{
	int	x;
	int	y;
	int	flag;

	y = 0;
	flag = 0;
	while (game->map.grid && game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == 'N'
				|| game->map.grid[y][x] == 'W'
				|| game->map.grid[y][x] == 'S'
				|| game->map.grid[y][x] == 'E')
			{
				search_pos(y, x, game);
				flag = 1;
			}
			x++;
		}
		y++;
	}
	if (flag == 0)
		print_err("Player not found !", game);
}
