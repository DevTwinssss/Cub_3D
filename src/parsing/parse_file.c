#include "../../includes/cub3d.h"

int open_file(char *str)
{
    int fd;

    fd = open(str, O_RDONLY);
    if (fd < 0)
        return (-1);
    return (fd);
}

int valide_name(char *str)
{
    char *ext;
    int fd;

    ext = ft_strrchr(str, '.');
    if (!ext || ft_strcmp(ext, ".ber") != 0)
    {
        printf("Error: invalid file or cannot open.\n");
        return (-1);
    }
    fd = open_file(str);
    return (fd);
}
