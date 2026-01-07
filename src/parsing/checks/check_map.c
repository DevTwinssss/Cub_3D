/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:49:38 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/07 16:49:38 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	check_wall(char *s, t_game *game)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '1' && s[i] != ' ')
			print_err("Invalid walls in map!", game);
		i++;
	}
}

void	check_empty(t_game *game, int i, int j)
{
	if (i <= 0 || i >= game->map.height - 1
		||j <= 0 || j >= (int)ft_strlen(game->map.grid[i]) - 1)
	{
		print_err("Map not surrended with walls !", game);
	}
	if (game->map.grid[i][j + 1] == ' ' || game->map.grid[i][j - 1] == ' ')
		print_err("0 is next to space!", game);
	if (game->map.grid[i + 1] && game->map.grid[i - 1])
	{
		if (j < (int)ft_strlen(game->map.grid[i + 1])
			&& game->map.grid[i + 1][j] == ' ')
		{
			print_err("0 is next to space!", game);
		}
		if (j < (int)ft_strlen(game->map.grid[i - 1])
			&& game->map.grid[i - 1][j] == ' ')
		{
			print_err("0 is next to space!", game);
		}
	}
}

void	check_ground(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.grid && game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == '0')
				check_empty(game, i, j);
			j++;
		}
		i++;
	}
}

void	check_map(t_game *game)
{
	int	i;

	i = 0;
	if (!game || !game->map.grid || game->map.height == 0)
		print_err("Map is empty!", game);
	while (i < game->map.height)
	{
		if (i == 0 || i == game->map.height - 1)
			check_wall(game->map.grid[i], game);
		i++;
	}
	check_ground(game);
}
