#include "../../includes/cub3d.h"


void load_textures(t_game *game)
{
	game->textures[0].img =  mlx_xpm_file_to_image(game->mlx, "src/textures/img1.xpm", 
		&game->textures[0].width, &game->textures[0].height);
	if (!game->textures[0].img)
	{
		perror("Error: Failed to load texture img1.xpm");
		exit(1);
	}
	game->textures[0].addr = (int *)mlx_get_data_addr(game->textures[0].img, &game->textures[0].bpp, 
		&game->textures[0].line_len, &game->textures[0].endian);

	//------------------------
	game->textures[1].img =  mlx_xpm_file_to_image(game->mlx, "src/textures/img1.xpm", 
		&game->textures[1].width, &game->textures[1].height);
	if (!game->textures[1].img)
	{
		perror("Error: Failed to load texture img1.xpm");
		exit(1);
	}
	game->textures[1].addr = (int *)mlx_get_data_addr(game->textures[1].img, &game->textures[1].bpp, 
		&game->textures[1].line_len, &game->textures[1].endian);

	//-------------------------------
	game->textures[2].img =  mlx_xpm_file_to_image(game->mlx, "src/textures/img1.xpm", 
		&game->textures[2].width, &game->textures[2].height);
	if (!game->textures[2].img)
	{
		perror("Error: Failed to load texture img1.xpm");
		exit(1);
	}
	game->textures[2].addr = (int *)mlx_get_data_addr(game->textures[2].img, &game->textures[2].bpp, 
		&game->textures[2].line_len, &game->textures[2].endian);

	//--------------------------------
	game->textures[3].img =  mlx_xpm_file_to_image(game->mlx, "src/textures/img1.xpm", 
		&game->textures[3].width, &game->textures[3].height);
	if (!game->textures[3].img)
	{
		perror("Error: Failed to load texture img1.xpm");
		exit(1);
	}
	game->textures[3].addr = (int *)mlx_get_data_addr(game->textures[3].img, &game->textures[3].bpp, 
		&game->textures[3].line_len, &game->textures[3].endian);

}


t_game *initialize()
{
	t_game *game;
	// int bit_per_pixel;
	// int line_len;
	// int endian;
	
	game = (t_game*) malloc(sizeof(t_game));
	game->player.player_angle = 180 * (PI / 180);
	game->player.x = (screenWidth)/2;
	game->player.y = (screenHeight)/2;
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
	game->win = mlx_new_window(game->mlx, screenWidth, screenHeight, "cub3d");
	load_textures(game);
	// game->img = mlx_new_image(game->mlx, screenWidth, screenHeight);
	// game->data = (int *) mlx_get_data_addr(game->img, &bit_per_pixel, &line_len, &endian);

	mlx_put_image_to_window(game->mlx, game->win, game->textures[0].img, 0, 0);

	return(game);
}
