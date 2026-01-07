/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:13:55 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/07 17:13:55 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}

int	parse_rgb_number(char *str, int *i, int *nb)
{
	while (str[*i])
	{
		if (str[*i] == ',' || str[*i] == ' ' || str[*i] == '\t'
			|| str[*i] == '\n' || str[*i] == '\r')
		{
			(*nb)++;
			return (0);
		}
		else if (!(str[*i] >= '0' && str[*i] <= '9'))
			return (1);
		(*i)++;
	}
	(*nb)++;
	return (0);
}

void	parse_rgb_string(char *str, int *coma, int *nb, t_game *game)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (parse_rgb_number(str, &i, nb) == 1)
				print_err("Rgb Syntax is wrong", game);
			continue ;
		}
		else if (str[i] == ',' || str[i] == ' '
			|| str[i] == '\t' || str[i] == '\n' || str[i] == '\r')
		{
			if (str[i] == ',')
				(*coma)++;
			i++;
			continue ;
		}
		else
			print_err("Rgb Syntax is wrong", game);
	}
}

void	check_rgb_syntax(char *str, t_game *game)
{
	int	coma;
	int	nb;

	coma = 0;
	nb = 0;
	parse_rgb_string(str, &coma, &nb, game);
	if (coma != 2 || nb != 3)
		print_err("Rgb Syntax is wrong", game);
}

int	parse_color(char *str, t_game *game)
{
	int	r;
	int	b;
	int	g;
	int	i;

	i = 0;
	check_rgb_syntax(str, game);
	r = ft_atoi(str + i);
	if (r < 0 || r > 255)
		print_err("Rgb Syntax is wrong", game);
	while (str[i] && str[i] != ',')
		i++;
	i++;
	g = ft_atoi(str + i);
	if (g < 0 || g > 255)
		print_err("Rgb Syntax is wrong", game);
	while (str[i] && str[i] != ',')
		i++;
	i++;
	b = ft_atoi(str + i);
	if (b < 0 || b > 255)
		print_err("Rgb Syntax is wrong", game);
	return ((r << 16) | (g << 8) | b);
}
