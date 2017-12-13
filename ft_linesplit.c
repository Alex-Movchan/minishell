#include "minishell.h"

static size_t	ft_sizeline()
{
	size_t	size;
	int		i;

	size = 1;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			while (line[++i] && line[i] != '"')
				;
		else if (line[i] == '\'')
			while (line[++i] && line[i] != '\'')
				;
		if (line[i] == ';')
			size++;
		i++;
	}
	return (size);
}

static int	ft_linelen(int len)
{
	int		i;

	i = len;
	while (line[i])
	{
		if (line[i] == '"')
			while (line[++i] && line[i] != '"')
				;
		else if (line[i] == '\'')
			while (line[++i] && line[i] != '\'')
				;
		if (line[i] == ';')
			break ;
		i++;
	}
	return (i);
}

char		**ft_linesplit()
{
	char	**res;
	int		size;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (!(res = malloc(sizeof(char*) * (ft_sizeline() + 1))))
		return (NULL);
	while (line[len])
	{
		size = ft_linelen(len);
		size -= len;
		res[i++] = ft_strndup(line + len, (size_t)size);
		len += size + 1;
	}
	res[i] = NULL;
	return (res);
}
