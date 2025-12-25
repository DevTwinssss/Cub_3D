#include "../../../includes/cub3d.h"

void check_wall(char *s)
{
    int i;

    i = 0;
    while(s[i] != '\0')
    {
        if(s[i] != '1' && s[i] != ' ')
            print_err("Invalide walls in map !");
        i++;
    }
}
void check_map(t_game *game)
{
    int i;

    i = 0;
    while(i < game->map.height)
    {
        if(i == 0 || i == game->map.width - 1)
        {
            check_wall(game->map.grid[i]);
                    
        }
        
        i++;
    }
    
}