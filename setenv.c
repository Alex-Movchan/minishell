#include "minishell.h"

static char	*collect_an_argument(char *s1, char *s2)
{
	char	*s;
	char	*res;

	s = ft_strjoin(s1, "=");
	res = ft_strjoin(s, s2);
	ft_strdel(&s);
	return (res);
}

static char	**ft_arreyjoin(char **tmp, char *str)
{
	char	**res;
	int		i;

	res = (char**)malloc(sizeof(char*) * (ft_arrey_size(tmp) + 1));
	i = -1;
	while (tmp[++i])
		res[i] = ft_strdup(tmp[i]);
	res[i++] = str;
	res[i] = NULL;
	return (res);
}

char		**ft_setenv(char **env, char *str, char *src)
{
	char	**tmp;
	char	*s;
	int		i;

	i = ft_search_line_env(env, str);
	s = collect_an_argument(str, src);
	if (i != ft_arrey_size(env))
	{
		ft_strdel(&(env[i]));
		env[i] = s;
		return (env);
	}
	tmp = ft_arreyjoin(env, s);
	ft_dell_arrey(env);
	return (tmp);
}