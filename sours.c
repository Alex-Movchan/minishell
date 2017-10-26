#include "minishell.h"

char	*ft_strchrrev(char *ctr, char c)
{
	int		i;
	char	*src;

	i = (int)ft_strlen(ctr);
	while (i >=0)
	{
		if (ctr[i] == c)
			break ;
		i--;
	}
	if (i == -1)
		return (NULL);
	while (i-- >= 0)
		ctr++;
	return (ctr);
}

void	ft_back_print(size_t len)
{
	size_t	i;

	i = len;
	while (i-- > 0)
		ft_putchar('\b');
	i = len;
	while (i-- > 0)
		ft_putchar(' ');
	while (len-- > 0)
		ft_putchar('\b');
}


t_file	*get_file(char *str, char **env)
{
	char	*src;
	char	*s;

	if (!str)
		return (NULL);
	if ((s = ft_strchrrev(str,  ';')))
	{
		if (*s && *s < 33)
			s++;
		if ((src = ft_strchrrev(s, ' ')))
			return (ft_search_file(src, (int)ft_strlen(src), NULL));
		else
			return (ft_search_comand(s, env));
	}
	else if ((src = ft_strchrrev(str, ' ')))
		return (ft_search_file(src, (int)ft_strlen(src), NULL));
	else
		return (ft_search_comand(str, env));
}


char	*ft_search_d_name(char **name, int *len)
{
	char	*src;
	char	*d_name;
	int		i;

	i = (int)ft_strlen(*name);
	while (--i >= 0)
	{
		if ((*name)[i] == '/')
			break ;
	}
	i++;
	if (i == 1)
		return (NULL);
	*len -= i;
	d_name = ft_strndup((*name), (size_t)i);
	src = ft_strdup((*name) + i);
	ft_strdel(name);
	*name = src;
	return (d_name);
}