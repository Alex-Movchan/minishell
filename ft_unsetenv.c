#include "minishell.h"

int		ft_search_line_env(char **env, char *str)
{
	size_t	len;
	int		i;

	i = -1;
	len = ft_strlen(str);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], str, len) && env[i][len] == '=')
			break ;
	}
	return (i);
}

static char		**ft_dell_elem_env(char **menv, int nbr)
{
	char	**env;
	int		i;
	int		j;

	env = (char**)malloc(sizeof(char*) * (ft_arrey_size(menv) + 1));
	i = -1;
	j = 0;
	while (menv[++i] != NULL)
	{
		if (i == nbr)
			continue ;
		env[j++] = ft_strdup(menv[i]);
	}
	env[j] = NULL;
	ft_dell_arrey(menv);
	return (env);
}

char	**ft_unsetenv(char **env, char **arg)
{
	int		i;

    if (arg[2] || !arg[1])
    {
        ft_printf("{fd}{red}unsetenv: many arguments{eoc}\n", 2);
        return (env);
    }
	i = ft_search_line_env(env, arg[1]);
	if (i != ft_arrey_size(env))
		return (ft_dell_elem_env(env, i));
	ft_printf("{fd}{red}Error %{fd}s Not faund{eoc}\n", 2, 2, arg[1], 2);
	return (env);
}
