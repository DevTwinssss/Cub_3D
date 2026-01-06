#include "../../includes/cub3d.h"

static char	**ft_free(char **str, int j)
{
	while (j >= 0)
		free(str[j--]);
	free (str);
	return (NULL);
}

static char	**ft_alloc(char const *s, char **str, int words, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (j < words && s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		k = i;
		while (s[k] != '\0' && s[k] != c)
			k++;
		str[j] = malloc((k - i + 1) * sizeof(char));
		if (str[j] == NULL)
			return (ft_free(str, j));
		k = 0;
		while (s[i] != c && s[i] != '\0')
			str[j][k++] = s[i++];
		if (s[i] == c || s[i] == '\0')
			str[j++][k] = '\0';
	}
	str[j] = NULL;
	return (str);
}

static int	ft_count_words(char c, char const *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			j++;
		i++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**str;
	char	**res;

	if (s == NULL)
		return (NULL);
	words = ft_count_words(c, s);
	str = (char **)malloc((words + 1) * sizeof(char *));
	if (str == NULL)
		return (0);
	if (words == 0)
	{
		str[0] = NULL;
		return (str);
	}
	res = ft_alloc(s, str, words, c);
	return (res);
}