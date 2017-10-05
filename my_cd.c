#include "minishell.h"

static char	*get_pwd(char **env, char *path)
{
	int		i;

	i = ft_search_line_env(env, path);
	if (i == ft_arrey_size(env))
	{
		ft_printf("{fd}cd: does not know %{fd}s {fd}directory\n", 2, 2, path, 2);
		return (NULL);
	}
	return (ft_strdup((env[i] + (ft_strlen(path) + 1))));
}

static char	*ft_search_in_home(char **env, char *arg)
{
	char	*path;
	char	*buf;

	if (arg[1] != '/')
	{
		ft_printf("{fd}cd: no such user or named directory: %{fd}s\n", 2, 2, arg + 1);
		return (NULL);
	}
	if (!(path = get_pwd(env, "HOME")))
		return (NULL);
	buf = ft_strjoin(path, arg + 1);
	ft_strdel(&path);
	return (buf);
}

static char	**ft_do_cd(char **env, char *path)
{
	char	buf[1024];

	if (getcwd(buf, 1024) == NULL)
	{
		ft_printf("{fd}Error getcwd\n", 2);
		ft_strdel(&path);
		return (env);
	}
	if (chdir(path) != 0)
	{
		ft_printf("{fd}cd: no such user or named directory: %{fd}s\n", 2, 2, path);
		ft_strdel(&path);
		return (env);
	}
	env = ft_setenv(env, "OLDPWD", buf);
	ft_bzero(buf, 1024);
	getcwd(buf, 1024);
	env = ft_setenv(env, "PWD", buf);
	return (env);
}

char		**ft_cd(char **env, char *arg)
{
	char	*path;

	if (!arg || !ft_strcmp(arg, "~") || !ft_strcmp(arg, "~/"))
		path = get_pwd(env, "HOME");
	else if (arg[0] == '-' && arg[1] == '\0')
		path = get_pwd(env, "OLDPWD");
	else if (arg[0] == '-' && arg[1] != '\0')
	{
		ft_printf("{fd}cd: no such user or named directory: %{fd}s\n", 2, 2, arg);
		return (env);
	}
	else if (arg[0] == '~')
		path = ft_search_in_home(env, arg);
	else
		path = ft_strdup(arg);
	return (path == NULL ? env : ft_do_cd(env, path));
}