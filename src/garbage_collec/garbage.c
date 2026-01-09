/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:14:38 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/07 15:14:38 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_game(t_game *game)
{
	int	i;

	game->config.no_path = NULL;
	game->config.so_path = NULL;
	game->config.we_path = NULL;
	game->config.ea_path = NULL;
	game->config.floor_color = -1;
	game->config.ceiling_color = -1;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->flag.so = 0;
	game->flag.no = 0;
	game->flag.ea = 0;
	game->flag.we = 0;
	game->flag.f = 0;
	game->flag.c = 0;
	game->current_line = NULL;
	i = 0;
	while (i < 4)
		game->textures[i++].img = NULL;
}

void	free_config(t_config *config)
{
	if (config->no_path)
	{
		free(config->no_path);
		config->no_path = NULL;
	}
	if (config->so_path)
	{
		free(config->so_path);
		config->so_path = NULL;
	}
	if (config->we_path)
	{
		free(config->we_path);
		config->we_path = NULL;
	}
	if (config->ea_path)
	{
		free(config->ea_path);
		config->ea_path = NULL;
	}
	config->floor_color = 0;
	config->ceiling_color = 0;
}

void	free_map(t_map *map)
{
	int	i;

	if (map->grid)
	{
		i = 0;
		while (i < map->height && map->grid[i])
		{
			free(map->grid[i]);
			map->grid[i] = NULL;
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
	map->height = 0;
	map->width = 0;
}

void	free_curr(t_game *game)
{
	if (game->current_line)
	{
		free(game->current_line);
		game->current_line = NULL;
	}
}

void	clean_graphics(t_game *game)
{
	int	i;

	i = 0;
	if (game->mlx)
	{
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		while (i < 4)
		{
			if (game->textures[i].img)
				mlx_destroy_image(game->mlx, game->textures[i].img);
			i++;
		}
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}
