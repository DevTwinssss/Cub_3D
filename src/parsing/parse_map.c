/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hind <hind@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:03:05 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/07 18:23:20 by hind             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	help_parse_map(char *line, t_game *game, int *map_start, size_t len)
{
	if (len == 1 || check_space(line) == 1)
		return (0);
	if (!(*map_start) && is_config_line(line, game) == 0)
		check_config(line, game);
	else if (is_map_line(line))
	{
		*map_start = 1;
		add_line_map(line, game);
	}
	else if (*map_start)
		return (-1);
	return (0);
}

void	flag_check(t_game *game)
{
	if (game->flag.no > 1 || game->flag.so > 1
		|| game->flag.we > 1 || game->flag.ea > 1
		|| game->flag.f > 1 || game->flag.c > 1)
	{
		print_err("Invalide Element !", game);
	}
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
		len = ft_strlen(line);
		if (help_parse_map(line, game, &map_start, len) == -1)
		{
			free(line);
			print_err("Map not valide !", game);
			return (-1);
		}
		if (game->map.width < (int)len)
			game->map.width = len - 2;
		free(line);
		line = get_next_line(fd);
	}
	make_map_rectangular(game);
	search_player(game);
	flag_check(game);
	return (0);
}
