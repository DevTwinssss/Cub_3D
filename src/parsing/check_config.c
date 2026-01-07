/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nahilal <nahilal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:58:56 by nahilal           #+#    #+#             */
/*   Updated: 2026/01/07 18:18:03 by nahilal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int is_config_line(char *line, t_game *game)
{
    if(ft_strncmp(line, "NO ", 3) == 0)
        game->flag.no++;
    else if(ft_strncmp(line, "SO ", 3) == 0)
        game->flag.so++;
    else if(ft_strncmp(line, "EA ", 3) == 0)
        game->flag.ea++;
    else if(ft_strncmp(line, "WE ", 3) == 0)
        game->flag.we++;
    else if(ft_strncmp(line, "F ", 2) == 0)
        game->flag.f++;
    else if(ft_strncmp(line, "C ", 2) == 0)
        game->flag.c++;
    else
        return(1);
    return(0);
}
