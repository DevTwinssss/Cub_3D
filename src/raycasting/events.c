#include "../../includes/cub3d.h"

int is_press(int keycode, t_game *game)
{
	if (keycode == N) //UP
		game->player.move_up = 1;
	if (keycode == S) //down
		game->player.move_down = 1;
	if (keycode == W) // left
		game->player.move_left = 1;
	if (keycode == E) // right
		game->player.move_right = 1;
	if(keycode == left_rotate)
		game->player.left_rot = 1;
	if(keycode == right_rotate)
		game->player.right_rot = 1;
	if (keycode == 65307) // esc
	{
		cleanup_game(game);
		exit(0);
	}
	return(0);
}

int release(int keycode, t_game *game)
{
	if (keycode == N) //UP
		game->player.move_up = 0;
	if (keycode == S) //down
		game->player.move_down = 0;
	if (keycode == W) // left
		game->player.move_left = 0;
	if (keycode == E) // right
		game->player.move_right = 0;
	if(keycode == left_rotate)
		game->player.left_rot = 0;
	if(keycode == right_rotate)
		game->player.right_rot = 0;
	return(0);
}

int	press(t_game *game)
{
	up_down(game);
	left_right(game);
	rotation(game);
	render_background(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

	return (0);
}
