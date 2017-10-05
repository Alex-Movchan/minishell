#include "minishell.h"

static void	ft_print_arg_env(char **env, char *path)
{
	int		i;

	i = ft_search_line_env(env, path);
	if (i == ft_arrey_size(env))
		return ;
	ft_printf("%s\n", (env[i] + (ft_strlen(path) + 1)));
}

static void	ft_print_arg(char *str)
{
	char *buf;

	if ((str[0] == '"' && str[ft_strlen(str)] == '"') ||
			(str[0] == '\'' && str[ft_strlen(str)] == '\''))
	{
		buf = ft_strndup(str + 1, ft_strlen(str) - 1);
		ft_printf("%s\n", buf);
		return (ft_strdel(&buf));
	}
	ft_printf("%s\n", str);
}

void		ft_echo(char **env, char *arg)
{
	char	*buf;

	if (arg[0] == '$' && ft_isalpha(arg[1]))
		return (ft_print_arg_env(env, arg + 1));
	else if (arg[0] == '$' && arg[1] == '{' &&
			arg[ft_strlen(arg)] == '}' && ft_isalpha(arg[2]))
	{
		buf = ft_strndup(arg + 2, ft_strlen(arg) -1);
		ft_print_arg_env(env, buf);
		ft_strdel(&buf);
	}
	else
		ft_print_arg(arg);
}