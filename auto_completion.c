
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

static void ft_search_line(char *c, t_file *file, int i)
{
	int		j;
	char	*src;

	src = (char*)line + i;
	j = (int)ft_strlen(src);
	while (--j >= 0)
		if (src[j] == '/')
			break;
	if (src[j] == '/')
	{
		i += j + 1;
		src = (char*)line + i;
	}
	src = ft_do_tab(file, src, c);
	j = -1;
	while (src[++j])
		line[i++] = src[j];
	caret = (int)ft_strlen((char*)line);
}

void		auto_completion(t_term *term,  char *c)
{
	t_file *file;
	int		len;
	int		i;

	i = caret;
	if (line[0] == '\0' || line[caret] != '\0')
		return ;
	if ((file = get_file(term->env, &i)))
	{
		len = last_file(file);
		ft_search_line(c, file, i);
		dell_file(file, len);
	}
	else
		ft_putchar('\a');
}
