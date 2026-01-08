/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 16:49:38 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/07 16:49:38 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	check_wall(char *s, t_game *game)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '1' && s[i] != ' ')
			print_err("Invalid walls in map!", game);
		i++;
	}
}

void	check_player_pos(t_game *game, int i, int j)
{
	int	len_next;
    int	len_prev;

    if (i == 0 || i == game->map.height - 1)
        print_err("Map not surrounded with walls!", game);
    if (j == 0 || game->map.grid[i][j - 1] == ' ')
        print_err("player is next to space!", game);
    if (game->map.grid[i][j + 1] == '\0' || game->map.grid[i][j + 1] == ' ')
        print_err("player is next to space!", game);
    if (game->map.grid[i - 1])
    {
        len_prev = ft_strlen(game->map.grid[i - 1]);
        if (j >= len_prev || game->map.grid[i - 1][j] == ' ')
            print_err("player is next to space!", game);
    }
    if (game->map.grid[i + 1])
    {
        len_next = ft_strlen(game->map.grid[i + 1]);
        if (j >= len_next || game->map.grid[i + 1][j] == ' ')
            print_err("player is next to space!", game);
    }
}
void	check_empty(t_game *game, int i, int j)
{
    int	len_next;
    int	len_prev;

    if (i == 0 || i == game->map.height - 1)
        print_err("Map not surrounded with walls!", game);
    if (j == 0 || game->map.grid[i][j - 1] == ' ')
        print_err("0 is next to space!", game);
    if (game->map.grid[i][j + 1] == '\0' || game->map.grid[i][j + 1] == ' ')
        print_err("0 is next to space!", game);
    if (game->map.grid[i - 1])
    {
        len_prev = ft_strlen(game->map.grid[i - 1]);
        if (j >= len_prev || game->map.grid[i - 1][j] == ' ')
            print_err("0 is next to space!", game);
    }
    if (game->map.grid[i + 1])
    {
        len_next = ft_strlen(game->map.grid[i + 1]);
        if (j >= len_next || game->map.grid[i + 1][j] == ' ')
            print_err("0 is next to space!", game);
    }
}

void	check_ground(t_game *game)
{
    int	i;
    int	j;

    i = 0;
    while (game->map.grid && game->map.grid[i])
    {
        j = 0;
        while (game->map.grid[i][j])
        {
            if (game->map.grid[i][j] == '0')
                check_empty(game, i, j);
            else if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S'
                || game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
                check_player_pos(game, i, j);
            j++;
        }
        i++;
    }
}

void	check_map(t_game *game)
{
	int	i;

	i = 0;
	if (!game || !game->map.grid || game->map.height == 0)
		print_err("Map is empty!", game);
	while (i < game->map.height)
	{
		if (i == 0 || i == game->map.height - 1)
			check_wall(game->map.grid[i], game);
		i++;
	}
	check_ground(game);
}
