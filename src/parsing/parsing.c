/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:27:02 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/07 17:27:02 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	parsing(char *str, t_game *game)
{
	int	fd;

	game->map.grid = NULL;
	game->map.height = 0;
	fd = valide_name(str);
	if (fd < 0)
		return (-1);
	parse_map(fd, game);
	validate_config(game);
	close(fd);
	return (0);
}
