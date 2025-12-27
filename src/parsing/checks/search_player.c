#include "../../../includes/cub3d.h"

void search_pos(int y,int x, t_game *game)
{
    if(game->map.grid[y][x] == 'N')
    {
        game->player.x = (double)x + 0.5;
        game->player.y = (double)y + 0.5;
        game->player.dir_x = 0.0;
        game->player.dir_y = -1.0;
        game->player.plane_x = 0.66;
        game->player.plane_y = 0.0;
    }
    else if(game->map.grid[y][x] == 'S')
    {
        game->player.x = (double)x + 0.5;
        game->player.y = (double)y + 0.5;
        game->player.dir_x = 0.0;
        game->player.dir_y = 1.0;
        game->player.plane_x = -0.66;
        game->player.plane_y = 0.0;
    }
    else if(game->map.grid[y][x] == 'E')
    {
        game->player.x = (double)x + 0.5;
        game->player.y = (double)y + 0.5;
        game->player.dir_x = 1.0;
        game->player.dir_y = 0.0;
        game->player.plane_x = 0.0;
        game->player.plane_y = 0.66;
    }
    else if(game->map.grid[y][x] == 'W')
    {
        game->player.x = (double)x + 0.5;
        game->player.y = (double)y + 0.5;
        game->player.dir_x = -1.0;
        game->player.dir_y = 0.0;
        game->player.plane_x = 0.0;
        game->player.plane_y = -0.66;
    }
}

void search_player(t_game *game)
{
    int x, y, flag;

    y = 0;
    x = 0;
    flag = 0;
    while(game->map.grid && game->map.grid[y] )
    {
        x = 0;
        while(game->map.grid[y][x])
        {
            if(game->map.grid[y][x] == 'N'
                || game->map.grid[y][x] == 'W'
                || game->map.grid[y][x] == 'S'
                || game->map.grid[y][x] == 'E')
            {
                search_pos(y, x, game);
                flag = 1;
            }
            x++;
        }
        y++;
    }
    if(flag == 0)
        print_err("Player not found !",game);   
}
