
#include "minishell.h"

void	ft_do_binari(char *path, char **arg, t_term *term)
{
	if ((pid = fork()) < 0)
		return;
	if (pid == 0)
	{
        signal(SIGINT, SIG_DFL);
		execve(path, arg, term->env);
	}
	else
		waitpid(pid, NULL, 0);
	pid = 0;
}

void	ft_do_shell(char **tmp_line, t_term **term)
{
	int		i;
	char	**arg;
	char	*path;

	i = -1;
	while (tmp_line[++i])
	{
		if (!(arg = ft_strsplit_quot(tmp_line[i])) || !arg[0])
			continue;
        if (!ft_strcmp(arg[0], "exit"))
            exit(0);
		else if (!ft_strcmp(arg[0], "env"))
			ft_env(arg, *term);
		else if (!ft_strcmp(arg[0], "unsetenv"))
			(*term)->env = ft_unsetenv((*term)->env, arg);
		else if (!ft_strcmp(arg[0], "setenv"))
			(*term)->env = ft_setenv((*term)->env, arg[1], arg[2]);
		else if (!ft_strcmp(arg[0], "cd"))
			(*term)->env = ft_cd((*term)->env, arg, term);
		else if ((path = call_binary((*term)->env, arg[0])))
        {
			ft_do_binari(path, arg, *term);
            ft_strdel(&path);
        }
        ft_dell_arrey(arg);
	}
    ft_dell_arrey(tmp_line);
}

void	do_monishell(t_term *term)
{
	t_lin	*lin;
	char	**arg;

	lin = NULL;
	while (1)
	{
		tcsetattr(0, TCSANOW, &term->not_canon);
		ft_putstr("\e[0;32m$>");
		read_line(&lin, term);
        ft_putstr("\e[0m");
		tcsetattr(0, TCSANOW, &term->canon);
		if (line[0] == '\0' || !(arg = ft_linesplit()))
			continue ;
		ft_do_shell(arg, &term);
	}
}
