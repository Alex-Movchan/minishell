
#include "minishell.h"

static int	last_file(t_file *file)
{
	t_file	*lst;
	int		i;

	i = 1;
	lst = file;
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	lst->next = file;
	return (i);
}

static char	*ft_do_tab(t_file *file, char *src, char *c)
{
	while (*c == '\t')
	{
		ft_back_print(ft_strlen(src));
		src = file->name;
		ft_putstr(src);
		if (file->next)
			file = file->next;
		read(0, c, 1);
	}
	return (src);
}

static void dell_file(t_file *lst, int len)
{
	t_file	*leaks;

	while (lst && len--)
	{
		leaks = lst;
		lst = lst->next;
		leaks->next = NULL;
		ft_strdel(&(leaks->name));
		free(leaks);
	}
}

static char	*ft_search_line(char *c, char *line, t_file *file)
{
	char	*buf;
	char	*src;
	char	*str;
	char	*tab;

	if ((buf = ft_strchrrev(line, ';')))
	{
		if ((src = ft_strchrrev(buf, '/')))
		{
			str = ft_do_tab(file, src, c);
			tab = ft_strndup(line, (ft_strlen(line) - ft_strlen(src)));
		}
		if ((src = ft_strchrrev(buf + 1, ' ')))
		{
			str = ft_do_tab(file, src, c);
			tab = ft_strndup(line, (ft_strlen(line) - ft_strlen(src)));
		}
		else
		{
			str = ft_do_tab(file, buf + 1, c);
			tab = ft_strndup(line, (ft_strlen(line) - ft_strlen(buf + 1)));
		}
	}
	else if ((buf = ft_strchrrev(line, ' ')))
	{
		if ((src = ft_strchrrev(buf, '/')))
		{
			str = ft_do_tab(file, src, c);
			tab = ft_strndup(line, (ft_strlen(line) - ft_strlen(src)));
		}
		else
		{
			str = ft_do_tab(file, buf, c);
			tab = ft_strndup(line, (ft_strlen(line) - ft_strlen(buf)));
		}
	}
	else
		return (ft_strdup(ft_do_tab(file, line, c)));
	line = ft_strjoin(tab, str);
	ft_strdel(&tab);
	return (line);
}

char		*auto_completion(char **env, char *line, char *c)
{
	t_file *file;
	int		len;
	char	*buf;

	if ((file = get_file(line, env)))
	{
		len = last_file(file);
		buf = ft_search_line(c, line, file);
		ft_strdel(&line);
		line = buf;
		dell_file(file, len);
	}
	else
		ft_putchar('\a');
	return (line);
}