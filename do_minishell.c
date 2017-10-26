#include "minishell.h"

static void		dell_histori(t_lin **lin)
{
	t_lin	*lst;
	t_lin	*leaks;

	lst = *lin;
	while (lst->prev)
		lst = lst->prev;
	while (lst)
	{
		leaks = lst;
		lst = lst->next;
		if (lst)
			lst->prev = NULL;
		leaks->next = NULL;
		ft_strdel(&(leaks->line));
		free(leaks);
	}
	*lin = NULL;
}

static int		ft_search_argum_exit(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] < 33)
		i++;
	if (ft_strncmp(str + i, "exit", 4))
		return (1);
	if (str[i + 5] > 33)
		return (1);
	if (str[i + 5] != '\0')
		ft_printf("%{fd}s%{fd}s%{fd}s\n", 2, "minishell: exit: ",
			2, str + (i + 5), 2, " numeric argument required");
	return (0);
}

void	ft_do_shell(char *line, char **env)
{
	int		i;
	char	**comand;

}

void	do_monishell(char **env)
{
	char	*line;
	t_lin	*lin;

	lin = NULL;
	while (1)
	{
		ft_putstr("$>");
		if (!(line = read_line(env, &lin)))
			continue ;
		else if (!ft_search_argum_exit(line))
			break ;
		else
			ft_do_shell(line, env);
	}
	dell_histori(&lin);
}