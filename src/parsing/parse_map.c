/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:03:05 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/09 01:44:27 by nahilal          ###   ########.fr       */
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
	int check;
	(void)len;

	check = is_config_line(line, game);
	if ((len == 1 || check_space(line) == 1) && *map_start != 1)
		return (0);
	if (!(*map_start) &&  check == 0)
		check_config(line, game);
	else if (check == 1)
	{
		if (is_map_line(line))
		{
			*map_start = 1;
			add_line_map(line, game);
		}
		else if (*map_start)
			return (-1);
		else
			print_err("Invalide Element",game);
	}
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

int check_line(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] != ' ')
			return(0);
		i++;	
	}
	return(-1);
}
void check_valide_map(t_game *game)
{
	int i;
	size_t len;

	i = 0;
	while(game->map.grid[i])
	{
		len = ft_strlen(game->map.grid[i]);
		if(len == 0)
			print_err("Invalide map!",game);
		else if(check_line(game->map.grid[i]) == -1)
			print_err("Invalide map!",game);
		i++;
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
		game->current_line = line;
		len = ft_strlen(line);
		if (help_parse_map(line, game, &map_start, len) == -1)
		{
			free(line);
			game->current_line = NULL;
			print_err("Map not valide !", game);
		}
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
