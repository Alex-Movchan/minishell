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

    if (!str || ! src)
    {
        ft_putstr_fd("\e[0;31msetenv: error arguments\e[0m\n", 2);
    }
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

void        ft_env(char **arg, t_term *term)
{
    int     i;
    
    i = -1;
    if (arg[1])
    {
        ft_putstr_fd("\e[0;31menv: meny arguments\e[0m\n", 2);
        return;
    }
    while (term->env[++i])
        ft_putendl(term->env[i]);
}
