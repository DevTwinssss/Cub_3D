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

int parse_color(char *str)
{
    int r, g, b;
    int i = 0;
    
    r = ft_atoi(str + i);
    while (str[i] && str[i] != ',')
        i++;
    i++; // skip comma  
    g = ft_atoi(str + i);
    while (str[i] && str[i] != ',')
        i++;
    i++; // skip comma
    
    b = ft_atoi(str + i);
    
    return ((r << 16) | (g << 8) | b);
}
