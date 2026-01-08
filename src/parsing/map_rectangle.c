/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rectangle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:05:40 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/08 01:38:20 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	make_map_rectangular(t_game *game)
{
	int		i;
	int		j;
	char	*new_line;
	int		len;

	i = 0;
	while (i < game->map.height)
	{
		len = ft_strlen(game->map.grid[i]);
		if (len < game->map.width)
		{
			new_line = malloc(sizeof(char) * (game->map.width + 1));
			if (!new_line)
				print_err("error in allocation", game);
			j = -1;
			while (++j < len)
				new_line[j] = game->map.grid[i][j];
			while (j < game->map.width)
				new_line[j++] = '1';
			new_line[j] = '\0';
			free(game->map.grid[i]);
			game->map.grid[i] = new_line;
		}
		i++;
	}
}
