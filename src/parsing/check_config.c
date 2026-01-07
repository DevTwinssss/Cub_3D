/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:58:56 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/07 18:04:33 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_config_line(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->flag.NO++;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->flag.SO++;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->flag.EA++;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->flag.WE++;
	else if (ft_strncmp(line, "F ", 2) == 0)
		game->flag.F++;
	else if (ft_strncmp(line, "C ", 2) == 0)
		game->flag.C++;
	else
		return (1);
	return (0);
}
