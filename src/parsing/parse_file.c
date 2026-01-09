/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:02:22 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/09 03:49:42 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	open_file(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	valide_name(char *str)
{
	char	*ext;
	int		fd;

	ext = ft_strrchr(str, '.');
	if (!ext || ft_strcmp(ext, ".cub") != 0)
	{
		printf("Error\ninvalid file or cannot open.\n");
		exit (1);
	}
	fd = open_file(str);
	return (fd);
}
