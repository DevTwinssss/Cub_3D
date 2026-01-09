/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:39:53 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/07 17:39:53 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	validate_config(t_game *game)
{
	if (!game->config.no_path)
		print_err("Missing NO texture path", game);
	if (!game->config.so_path)
		print_err("Missing SO texture path", game);
	if (!game->config.we_path)
		print_err("Missing WE texture path", game);
	if (!game->config.ea_path)
		print_err("Missing EA texture path", game);
	if (game->config.floor_color == -1)
		print_err("Missing F color", game);
	if (game->config.ceiling_color == -1)
		print_err("Missing C color", game);
}

void	remove_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			str[i] = '\0';
			return ;
		}
		i++;
	}
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

char	*skip_spaces_and_dup(char *str)
{
	int		i;
	int		start;
	int		len;
	char	*result;

	i = 0;
	while (str[i] == ' ')
		i++;
	start = i;
	len = 0;
	while (str[i] && str[i] != '\n' && str[i] != '\r')
	{
		len++;
		i++;
	}
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = str[start + i];
		i++;
	}
	result[len] = '\0';
	return (result);
}

int	check_config(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		game->config.no_path = skip_spaces_and_dup(line + 3);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		game->config.so_path = skip_spaces_and_dup(line + 3);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		game->config.we_path = skip_spaces_and_dup(line + 3);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		game->config.ea_path = skip_spaces_and_dup(line + 3);
	}
	else if (check_floor_ceiling(line, game) == 1)
		return (1);
	else
		return (0);
	return (1);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (-1);
	while (line[i])
	{
		
		if (!ft_strchr("01NSEW \n\r", line[i]))
			return (-1);
		i++;
	}
	return (1);
}
