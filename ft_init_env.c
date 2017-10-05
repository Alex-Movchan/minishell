#include "minishell.h"

char	**ft_init_env(char **env)
{
	char	**tmp;
	int		i;
	int		size;

	size = ft_arrey_size(env);
	tmp = (char**)malloc(sizeof(char*) * size + 1);
	i = -1;
	while (++i < size)
		tmp[i] = ft_strdup(env[i]);
	tmp[i] = NULL;
	return (tmp);
}