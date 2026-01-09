/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:03:05 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/09 03:24:43 by nahilal          ###   ########.fr       */
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
	int	check;

	check = is_config_line(line, game);
	if ((len == 1 || check_space(line) == 1) && *map_start != 1)
		return (0);
	if (!(*map_start) && check == 0)
		check_config(line, game);
	else if (check == 1)
	{
		
		if (is_map_line(line) == 1)
		{
			*map_start = 1;
			add_line_map(line, game);
		}
		else if (*map_start)
			return (-1);
		else 
			print_err("Invalide Element", game);
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

int	check_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (-1);
}

void	check_valide_map(t_game *game)
{
	int		i;
	size_t	len;

	i = 0;
	while (game->map.grid[i])
	{
		printf("%s\n",game->map.grid[i]);
		len = ft_strlen(game->map.grid[i]);
		if (len == 0)
			print_err("Invalide map!", game);
		else if (check_line(game->map.grid[i]) == -1)
			print_err("Invalide map!", game);
		i++;
	}
}
