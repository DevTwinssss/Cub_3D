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

void	error_free(char *line, t_game *game)
{
	free(line);
	game->current_line = NULL;
	print_err("Map not valide !", game);
}

int	parse_map(int fd, t_game *game)
{
	char	*line;
	size_t	len;
	int		map_start;

	map_start = 0;
	game->map.width = 0;
	line = get_next_line(fd);
	while (line)
	{
		game->current_line = line;
		len = ft_strlen(line);
		if (help_parse_map(line, game, &map_start, len) == -1)
			error_free(line, game);
		if (game->map.width < (int)len)
			game->map.width = len - 1;
		free(line);
		game->current_line = NULL;
		line = get_next_line(fd);
	}
	check_valide_map(game);
	search_player(game);
	flag_check(game);
	return (0);
}

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
