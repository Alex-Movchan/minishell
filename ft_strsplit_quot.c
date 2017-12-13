#include "minishell.h"

static size_t	ft_sizeatgum(char *str)
{
	int		i;
	size_t	size;

	size = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			while (str[++i] && str[i] != '"')
				;
		else if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		if (str[i] == ' ')
			size++;
		i++;
	}
	return (size);
}

static	size_t	ft_sizeline(char *str, size_t len)
{
	size_t	i;

	i = len;
	while (str[i])
	{
		if (str[i] == '"')
			while (str[++i] && str[i] != '"')
				;
		else if (line[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		if (str[i] == ' ')
			break ;
		i++;
	}
	return (i);
}

static char *ft_strnospace(char *str)
{
    char    *src;
    int     start;
    size_t  finish;
    
    finish = ft_strlen(str);
    start = 0;
    while (str[start] && (str[start] == ' ' || str[start] == '\t'))
        start++;
    while (finish > 0)
    {
        if (str[finish] > 33)
            break;
        finish--;
    }
    src = ft_strndup(str + start, finish + 1);
    return (src);
}

char		**ft_strsplit_quot(char *str)
{
	char	**res;
    char    *src;
	size_t	size;
	size_t	len;
	int		i;

	len = 0;
	i = 0;
    src = ft_strnospace(str);
	if (!(res = malloc(sizeof(char*) * (ft_sizeatgum(src) + 1))))
		return (NULL);
	while (src[len])
	{
		size = ft_sizeline(src, len);
		size -= len;
		res[i++] = ft_strndup(src + len, (size_t)size);
        if (src[len + size] == '\0')
            break;
		len += size + 1;
	}
	res[i] = NULL;
    ft_strdel(&src);
	return (res);
}
