#include "minishell.h"

static	t_lin	*ft_add_line(char *line, t_lin *histor)
{
	t_lin	*lst;

	lst = (t_lin*)malloc(sizeof(t_lin));
	lst->lin = line;
	if (histor)
	{
		lst->next = histor;
		histor->prev = lst;
	}
	return (lst);
}

void	ft_read_comand(char **env, t_lin *histor)
{
	char	*line;
	char	*buf;
	char	*leaks;

	buf = NULL;
	line = NULL;
	while (read(0, buf, 1) == 1)
	{
		if (buf[0] == '\n')
		{
			env = ft_do_comand(env, line);
			histor = ft_add_line(line, histor);
			line = NULL;
		}
		if (buf[0] == '\t')
		{
			auto_completion(line, env);
		}
		leaks = line;
		if (!line)
			line = buf;
		else
			line = ft_strjoin(line, buf);
		ft_strdel(&leaks);
	}
}