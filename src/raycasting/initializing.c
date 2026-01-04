#include "../../includes/cub3d.h"

void load_textures(t_game *game)
{
	int i;

	i = 0;
	char *paths[4] = {
        game->config.no_path, 
        game->config.so_path, 
        game->config.we_path, 
        game->config.ea_path
    };
	while (i < 4)
	{
		game->textures[i].img =  mlx_xpm_file_to_image(game->mlx, paths[i], 
			&game->textures[i].width, &game->textures[i].height);
		if (!game->textures[i].img)
		{
			perror("Error: Failed to load texture");
			exit(1);
		}
		game->textures[i].addr = (int *)mlx_get_data_addr(game->textures[i].img, &game->textures[i].bpp, 
			&game->textures[i].line_len, &game->textures[i].endian);
		i++;
	}
}

void init_graphics(t_game *game)
{
	int bit_per_pixel;
	int line_len;
	int endian;

	game->player.move_up = 0;
	game->player.move_down = 0;
	game->player.move_left = 0;
	game->player.move_right = 0;
	game->player.left_rot = 0;
	game->player.right_rot = 0;
	game->player.distance = 0;
	game->player.dir_x =  cos(game->player.player_angle);
	game->player.dir_y =  sin(game->player.player_angle);
	game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("Error\nMLX init failed\n");
        exit(1);
    }
	game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "cub3d");
	load_textures(game);
	game->img = mlx_new_image(game->mlx, screenWidth, screenHeight);
	game->data = (int *) mlx_get_data_addr(game->img, &bit_per_pixel, &line_len, &endian);
}
