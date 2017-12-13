#include "minishell.h"

int		ft_arrey_size(char **tmp)
{
	int		i;

	i = 0;
	while (tmp[i] != NULL)
		i++;
	return (i);
}

void		ft_dell_arrey(char **tmp)
{
	int		i;

	i = -1;
    if (!tmp)
        return;
	while (tmp[++i] != NULL)
		ft_strdel(&(tmp[i]));
	free(tmp);
	tmp = NULL;
}
