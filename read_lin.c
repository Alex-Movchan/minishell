#include "minishell.h"

static t_lin	*ft_add_line(char *line, t_lin *histor)
{
	t_lin	*lst;
	t_lin	*leaks;

	if (!line)
		return (histor);
	lst = (t_lin*)malloc(sizeof(t_lin));
	lst->line = line;
	lst->flag = 0;
	lst->prev = NULL;
	lst->next = NULL;
	if (histor)
	{
		while (histor->prev)
			histor = histor->prev;
		if (histor->flag == 1)
		{
			leaks = histor;
			histor = histor->next;
			histor->prev = NULL;
			ft_strdel(&(leaks->line));
			free(leaks);
		}
		lst->next = histor;
		histor->prev = lst;
	}
	return (lst);
}

static char		*add_in_line(char *line, char c)
{
	char	*src;
	int		i;

	i = -1;
	if (line)
	{
		src = ft_strnew(ft_strlen(line) + 1);
		while (line[++i])
			src[i] = line[i];
		src[i++] = c;
		src[i] = '\0';
		ft_strdel(&line);
	}
	else
	{
		src = ft_strnew(1);
		src[++i] = c;
		src[++i] = '\0';
	}
	return (src);
}

static char		*ft_dell_lastchr(char *str)
{
	char	*src;

	if (!str)
		return (NULL);

	ft_back_print(1);
	//ft_putstr(tgetstr("dc", NULL));
	if (str[1] == '\0')
		src = NULL;
	else
		src = ft_strndup(str, ft_strlen((str) + 1));
	ft_strdel(&str);
	return (src);
}

void			ft_put_quot(char quot)
{
	if (quot == '"')
		ft_putstr("dquote>");
	else if (quot == '\'')
		ft_putstr("quote>");
}

static char		*ft_get_quot(char *line, char quot)
{
	char	*src;
	char	*leaks;
	char	c;

	ft_put_quot(quot);
	src = NULL;
	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		if (ft_isprint((int)c) || c == '\n')
		{
			ft_putchar(c);
			src = add_in_line(src, c);
		}
		if (c == quot)
		{
			leaks = line;
			line = ft_strjoin(line, src);
			ft_strdel(&leaks);
			ft_strdel(&src);
			break ;
		}
		if (c == 127)
			src = ft_dell_lastchr(src);
		if (c == '\n')
		{
			leaks = line;
			line = ft_strjoin(line, src);
			ft_strdel(&leaks);
			ft_strdel(&src);
			ft_put_quot(quot);
		}
	}
	return (line);
}

char			*read_line(char **env, t_lin **lst)
{
	char	*left;
	char	c;
	char	quot;

	left = NULL;
	quot = 0;
	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		if (c == 127)
			left = ft_dell_lastchr(left);
		if (c == '\t')
			left = auto_completion(env, left, &c);
		if (quot == 0 && (c == '"' || c == '\''))
				quot = c;
		if (c == 27)
			left = ft_arrows(lst, left);
		if (c == '\n')
		{
			ft_putchar(c);
			if (quot == 0)
			{
				*lst = ft_add_line(left, *lst);
				return (left);
			}
			left = ft_get_quot(add_in_line(left, c), quot);
			quot = 0;
		}
		if (ft_isprint((int)c))
		{
			ft_putchar(c);
			left = add_in_line(left, c);
		}
	}
	return (NULL);
}