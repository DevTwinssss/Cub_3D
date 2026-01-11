/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_line_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:57:51 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/07 16:57:51 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*check_valide_path_conf(char *s, t_game *game)
{
	char	*str;

	str = ft_strrchr(s, '.');
	if (!str || ft_strcmp(str, ".xpm") != 0)
		print_err("invalid extension", game);
	return (s);
}

void	help_add_line(t_game *game, char **new_grid, int i, char *cleaned_line)
{
	new_grid[i] = cleaned_line;
	new_grid[i + 1] = NULL;
	free(game->map.grid);
	game->map.grid = new_grid;
	game->map.height++;
}

void	add_line_map(char *line, t_game *game)
{
	char	**new_grid;
	char	*cleaned_line;
	int		i;
	int		len;

	new_grid = malloc(sizeof(char *) * (game->map.height + 2));
	if (!new_grid)
		exit (1);
	i = 0;
	while (i < game->map.height)
	{
		new_grid[i] = game->map.grid[i];
		i++;
	}
	cleaned_line = ft_strdup(line);
	len = ft_strlen(cleaned_line);
	while (len > 0 && (cleaned_line[len - 1] == '\n'
			|| cleaned_line[len - 1] == '\r'))
	{
		cleaned_line[len - 1] = '\0';
		len--;
	}
	help_add_line(game, new_grid, i, cleaned_line);
}
