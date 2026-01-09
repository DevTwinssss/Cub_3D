/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:58:56 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/10 00:37:14 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_config_line(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		game->flag.no++;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		game->flag.so++;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		game->flag.ea++;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		game->flag.we++;
	else if (ft_strncmp(line, "F ", 2) == 0)
		game->flag.f++;
	else if (ft_strncmp(line, "C ", 2) == 0)
		game->flag.c++;
	else
		return (1);
	return (0);
}

int	check_floor_ceiling(char *line, t_game *game)
{
	if (line[0] == 'F')
	{
		game->config.floor_color = parse_color(line + 2, game);
		return (1);
	}
	else if (line[0] == 'C')
	{
		game->config.ceiling_color = parse_color(line + 2, game);
		return (1);
	}
	return (0);
}

int	check_es_we(t_game *game, char *line)
{
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (game->config.we_path)
			free(game->config.we_path);
		game->config.we_path = skip_spaces_and_dup(line + 3);
		return (1);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (game->config.ea_path)
			free(game->config.ea_path);
		game->config.ea_path = skip_spaces_and_dup(line + 3);
		return (1);
	}
	return (0);
}

int	check_config(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (game->config.no_path)
			free(game->config.no_path);
		game->config.no_path = skip_spaces_and_dup(line + 3);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (game->config.so_path)
			free(game->config.so_path);
		game->config.so_path = skip_spaces_and_dup(line + 3);
	}
	else if (check_es_we(game, line) == 1)
		return (1);
	else if (check_floor_ceiling(line, game) == 1)
		return (1);
	else
		return (0);
	return (1);
}
