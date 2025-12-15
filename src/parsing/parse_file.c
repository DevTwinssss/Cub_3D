#include "../../includes/cub3d.h"

int	valide_name(char *str)
{
	char	*s1 ;

	s1 = ft_strrchr(str, '.');
	if (!s1 || ft_strlen(s1) != ft_strlen(".ber"))
		return (0);
	if (ft_strcmp(s1, ".ber") != 0)
		return (0);
	return (1);
}


