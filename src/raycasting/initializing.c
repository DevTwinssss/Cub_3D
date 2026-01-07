/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:55:15 by hind              #+#    #+#             */
/*   Updated: 2026/01/07 17:01:17 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	load_textures(t_game *game)
{
	int		i;
	char	*paths[4];

	paths[0] = game->config.no_path;
	paths[1] = game->config.so_path;
	paths[2] = game->config.we_path;
	paths[3] = game->config.ea_path;
	i = 0;
	while (i < 4)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx, paths[i],
				&game->textures[i].width, &game->textures[i].height);
		if (!game->textures[i].img)
		{
			perror("Error: Failed to load texture");
			exit(1);
		}
		game->textures[i].addr = (int *)mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].bpp, &game->textures[i].line_len,
				&game->textures[i].endian);
		i++;
	}
}

int	close_handler(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

void	initialize_mlx(t_game *game)
{
	int	bit_per_pixel;
	int	line_len;
	int	endian;

	game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "cub3d");
	game->img = mlx_new_image(game->mlx, screenWidth, screenHeight);
	game->data = (int *) mlx_get_data_addr(game->img, &bit_per_pixel,
			&line_len, &endian);
	mlx_hook(game->win, 2, 1L << 0, is_press, game);
	mlx_hook(game->win, 3, 1L << 1, release, game);
	mlx_hook(game->win, 17, 0, close_handler, game);
	mlx_loop_hook(game->mlx, press, game);
}

void	init_graphics(t_game *game)
{
	game->player.move_up = 0;
	game->player.move_down = 0;
	game->player.move_left = 0;
	game->player.move_right = 0;
	game->player.left_rot = 0;
	game->player.right_rot = 0;
	game->player.distance = 0;
	game->player.dir_x = cos(game->player.player_angle);
	game->player.dir_y = sin(game->player.player_angle);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		printf("Error MLX init failed\n");
		exit(1);
	}
	load_textures(game);
	initialize_mlx(game);
}
