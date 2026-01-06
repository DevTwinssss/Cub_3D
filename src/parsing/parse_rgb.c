#include "../../includes/cub3d.h"

int ft_atoi(const char *str)
{
    int i = 0;
    int result = 0;
    
    while (str[i] == ' ')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result);
}


void check_rgb_syntax(char *str,t_game *game)
{
    int i;
    int coma;
    int nb;

    i = 0;
    coma = 0;
    nb = 0;
    while(str[i])
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            while(str[i])
            {
                if(str[i] == ',' || str[i] == ' '|| str[i] == '\t' || str[i] == '\n' || str[i] == '\r')
                {
                    nb++;
                    break;
                }
                else if(!(str[i] >= '0' && str[i] <= '9'))
                    break;
                i++;
            }
            continue;
        }
        else if(str[i] == ',' || str[i] == ' '
            || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')
        {
            if(str[i] == ',')
                coma++;
            i++;
            continue;
        }
        else
            print_err("Rgb Syntax is wrong",game);
    }
    if(coma != 2 || nb != 3)
            print_err("Rgb Syntax is wrong",game);
}

int parse_color(char *str, t_game *game)
{
    int r, g, b;
    int i;
    i = 0;

    // check_split(str);
    check_rgb_syntax(str,game);
    r = ft_atoi(str + i);
    if(r < 0 || r > 255)
        print_err("Rgb Syntax is wrong",game);
    while (str[i] && str[i] != ',')
        i++;
    i++;
    g = ft_atoi(str + i);
    if(g < 0 || g > 255)
        print_err("Rgb Syntax is wrong",game);
    while (str[i] && str[i] != ',')
        i++;
    i++;
    b = ft_atoi(str + i);
    if(b < 0 || b > 255)
        print_err("Rgb Syntax is wrong",game);
    return ((r << 16) | (g << 8) | b);
}

