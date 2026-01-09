/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanip.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 23:47:03 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/09 23:47:33 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	cleanup_game(t_game *game)
{
	int	i;

	i = 0;
	get_next_line(-1);
	if (game->current_line)
	{
		free(game->current_line);
		game->current_line = NULL;
	}
	free_config(&game->config);
	free_map(&game->map);
	clean_graphics(game);
	free(game);
}
