
#include "minishell.h"

static t_lin	*ft_add_line(t_lin *histor)
{
	t_lin	*lst;
	t_lin	*leaks;

	if (line[0] == '\0')
		return (histor);
	lst = (t_lin*)malloc(sizeof(t_lin));
	lst->line = ft_strdup((char*)line);
	lst->caret = (int)ft_strlen((char*)line);;
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

void    ft_delete()
{
    int j;
    
    ft_termcap_do("sc");
    ft_termcap_do("cd");
    j = caret - 1;
    while (line[++j])
        line[j] = line[j + 1];
    ft_putstr(line + caret);
    ft_termcap_do("rc");

}

static void		ft_dell_lastchr()
{
	int j;

	if (caret > 0)
	{
        ft_clearline();
		j = caret - 2;
		while (line[++j])
			line[j] = line[j + 1];
        caret--;
        ft_putstr(line);
        ft_return_cursor(size_colum(), (int)ft_strlen(line), caret, line);
	}
}

//static void        ft_putlinequot(char c)
//{
//    if (c == '"')
//        ft_putstr("dquote>");
//    else if (c == '\'')
//        ft_putstr("quote>");
//}


int			size_colum(void)
{
    struct winsize	size;
    
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
    return ((int)size.ws_col);
}

static void		ft_addinline(char c)
{
	int		i;
	int		j;
	char	tmp;
	char	next;
    
    if (line[caret] == '\0')
    {
        line[caret++] = c;
        return (ft_putchar(c));
    }
    i = (int)ft_strlen((char*)line);
    j = caret;
    tmp = line[j];
    while (j < i)
    {
        next = line[j + 1];
        line[j + 1] = tmp;
        tmp = next;
        j++;
    }
    line[caret] = c;
    ft_termcap_do("cd");
    ft_putstr(line + caret);
    ft_return_cursor(size_colum(), (int)ft_strlen(line), ++caret, line);
}

//static int        ft_quota(char quot, char *c, int size)
//{
//
//    ft_addinline(quot);
//    while (read(STDIN_FILENO, c, 1) > 0)
//    {
//        if (*c == quot)
//            break;
//        if (ft_isprint((int) *c) || *c == '\n')
//        {
//            caret += size;
//            ft_addinline(*c);
//            caret -= size;
//        }
//        if (*c == '\n')
//        {
//            ft_putlinequot(quot);
//            size += caret;
//            caret = 0;
//        }
//        if (*c == 127)
//            ft_dell_lastchr();
//    }
//    return(size + caret);
//}

void			read_line(t_lin **lst, t_term *term)
{
	char	c;
	int		size;

	caret = 0;
	size = 0;
	ft_bzero((void*)line, MAX_LINE_SIZE);
	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		if (c == '\t')
			auto_completion(term, &c);
		if (c == 127)
			ft_dell_lastchr();
		if (c == 27)
			ft_arrows(lst);
//		if (c == '\'' || c == '"')
//			size = ft_quota(c, &c, size);
		if (c == '\n')
		{
            ft_end_cursor();
			ft_putchar('\n');
			caret += size;
			*lst = ft_add_line(*lst);
			return;
		}
		if (ft_isprint((int) c))
		{
			caret += size;
			ft_addinline(c);
			caret -= size;
		}
	}
}
