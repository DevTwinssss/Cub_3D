/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:30:41 by hind              #+#    #+#             */
/*   Updated: 2026/01/07 17:30:46 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
	{
		printf("Usage: ./Cub3d <map.cub>\n");
		return (1);
	}
	game = malloc(sizeof(t_game));
	if (!game)
	{
		perror("Error\n Malloc failed\n");
		return (1);
	}
	init_game(game);
	if (parsing(av[1], game) == -1)
		print_err("File not found", game);
	check_map(game);
	make_map_rectangular(game);
	init_graphics(game);
	mlx_loop(game->mlx);
	cleanup_game(game);
	return (0);
}
