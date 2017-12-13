#include "minishell.h"

void	ft_back_print(size_t len)
{
	size_t	i;

	i = len;
	while (i-- > 0)
        ft_termcap_do("le");
    ft_termcap_do("dc");
      
}

t_file	*get_file(char **env, int *i)
{
	char	*src;
	t_file	*file;

	if (line[(*i)] < 33)
		(*i)--;
	while (*i > 0 && line[(*i)] > 32)
		(*i)--;
	if (line[(*i)] == ' ')
		(*i)++;
	src = ft_strndup((char*)line + (*i), (size_t)caret);
	if (((*i) == 0 || (line[(*i)] == ' ' && line[(*i) - 1] == ';')) && !ft_strchr(src, '/'))
		file = ft_search_comand(src, env);
	else
		file = ft_search_file(src, (int)ft_strlen(src), NULL);
	ft_strdel(&src);
	return (file);
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
