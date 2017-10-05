#include "minishell.h"

static char	*ft_accses(char **path, char *name)
{
	int		i;
	char	*buf;
	char	*filename;

	i = -1;
	while (path[++i])
	{
		buf = ft_strjoin(path[i], "/");
		filename = ft_strjoin(buf, name);
		ft_strdel(&buf);
		if (access(filename, 0) == 0)
		{
			if (access(filename, 1) == -1)
			{
				ft_printf("{fd}Error permission denied: %{fd}s\n", 2, 2, name);
				return (NULL);
			}
			return (filename);
		}
		ft_strdel(&filename);
	}
	ft_printf("{fd}Error command not found: %{fd}s\n", 2, 2, name);
	return (NULL);
}

char		*call_binary(char **my_env, char *name)
{
	int		i;
	char	**path;
	char	*comandname;

	i = ft_search_line_env(my_env, "PATH");
	if (i == ft_arrey_size(my_env))
	{
		ft_printf("{fd}Error command not found: %{fd}s\n", 2, 2, name);
		return (NULL);
	}
	path = ft_strsplit(my_env[i] + 5, ':');
	comandname = ft_accses(path, name);
	ft_dell_arrey(path);
	return (comandname);
}