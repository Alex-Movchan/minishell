#include "minishell.h"

static char	*ft_search_in_home(char **env, char *arg, t_term *term)
{
	char	*path;
	char	*buf;

	if (arg[1] != '/')
	{
		ft_printf("{fd}{red}cd: no such user or named directory: %{fd}s{eoc}\n", 2, 2, arg + 1);
		return (NULL);
	}
    if (term->home)
        path = ft_strdup(term->home);
    else
        return (NULL);
	buf = ft_strjoin(path, arg + 1);
	ft_strdel(&path);
	return (buf);
}

static char	*get_pwd(char **env, char *path)
{
    int		i;
    
    i = ft_search_line_env(env, path);
    if (i == ft_arrey_size(env))
    {
        ft_printf("{fd}{red}cd: does not know %{fd}s {fd}directory{eoc}\n", 2, 2, path, 2);
        return (NULL);
    }
    return (ft_strdup((env[i] + (ft_strlen(path) + 1))));
}

static char	**ft_do_cd(char **env, char *path, t_term **term)
{
	char	buf[1024];

	if (getcwd(buf, 1024) == NULL)
	{
		ft_printf("{fd}{red}Error getcwd{eoc}\n", 2);
		ft_strdel(&path);
		return (env);
	}
	if (chdir(path) != 0)
	{
		ft_printf("{fd}{red}cd: no such user or named directory: %{fd}s{eoc}\n", 2, 2, path);
		ft_strdel(&path);
		return (env);
	}
	env = ft_setenv(env, "OLDPWD", buf);
    ft_strdel(&(*term)->odpwd);
    (*term)->odpwd = ft_strdup(buf);
	ft_bzero(buf, 1024);
	getcwd(buf, 1024);
	env = ft_setenv(env, "PWD", buf);
    ft_strdel(&path);
	return (env);
}

char		**ft_cd(char **env, char **arg, t_term **term)
{
	char	*path;

    if (arg[1] && arg[2] != NULL)
    {
        ft_putstr_fd("\e[0;31mcd: too many arguments\e[0m\n", 2);
        return (env);
    }
	if (!arg[1] || !ft_strcmp(arg[1], "~") || !ft_strcmp(arg[1], "~/"))
        path = (*term)->home == NULL ? get_pwd(env, "HOME") : ft_strdup((*term)->home);
	else if (!ft_strcmp(arg[1], "-"))
    {
        path = (*term)->odpwd == NULL ? get_pwd(env, "OLDPWD") : ft_strdup((*term)->odpwd);
        ft_putendl(path);
    }
	else if (arg[1][0] == '-' && arg[1][1] != '\0')
	{
		ft_printf("{fd}{red}cd: no such user or named directory: %{fd}s{eoc}\n", 2, 2, arg);
		return (env);
	}
	else if (arg[1][0] == '~')
		path = ft_search_in_home(env, arg[1], *term);
	else
		path = ft_strdup(arg[1]);
	return (path == NULL ? env : ft_do_cd(env, path, term));
}
