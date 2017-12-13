#include "minishell.h"

static void	ft_now_line(t_lin **lin)
{
	t_lin	*now;

	now = (t_lin*)malloc(sizeof(t_lin));
	if (line[0] != '\0')
		now->line = ft_strdup((char*)line);
	else
		now->line = NULL;
	now->flag = 1;
	now->caret = (int)ft_strlen((char*)line);
	now->prev = NULL;
	now->next = *lin;
	(*lin)->prev = now;
	(*lin) = now;
}

static void	ft_arrows_up(t_lin **lin)
{

	if (*lin)
	{
		if (!(*lin)->prev && (*lin)->flag != 1)
			ft_now_line(lin);
		else if (!(*lin)->prev && (*lin)->flag == 1)
		{
			ft_strdel(&(*lin)->line);
			(*lin)->caret = (int)ft_strlen(line);
			(*lin)->line = ft_strdup(line);
		}
		if (line[0] != '\0')
		{
            ft_clearline();
			ft_bzero((void*)line, ft_strlen((char*)line));
		}
		if ((*lin)->flag == 1)
			(*lin) = (*lin)->next;
		ft_strcpy((char*)line, (*lin)->line);
		caret = (*lin)->caret;
		ft_putstr((char*)line);
		if ((*lin)->next)
			*lin = (*lin)->next;
	}
}

static void	ft_arrows_down(t_lin **lin)
{
	if (*lin && (*lin)->prev)
	{
		if (line[0] != '\0')
		{
            ft_clearline();
			ft_bzero((void*)line, ft_strlen((char*)line));
		}
		if ((*lin)->prev->line)
			ft_strcpy((char*)line, (*lin)->prev->line);
		else
			ft_bzero((void*)line, ft_strlen((char*)line));
		caret = (int)ft_strlen(line);
		ft_putstr((char*)line);
		if ((*lin)->prev)
			*lin = (*lin)->prev;
	}
}

void    ft_do_arrow(int size_line, int len)
{
    int     v1;
    int     v2;
    int     h1;
    int     h2;
    
    v1 = ft_add_vertical(size_line, &h1, caret);
    v2 = ft_add_vertical(size_line, &h2, len);
    if (v2 == 0 && v1 != 0)
        h2 += 2;
    v2 -= v1;
    h2 -= h1;
    if (h2 > 0)
        while(h2--)
            ft_termcap_do("nd");
    else if (h2 < 0)
        while (h2++)
            ft_termcap_do("le");
    if (v2 > 0)
        while (v2--)
            ft_termcap_do("do");
    else if (v2 < 0)
        while (v2++)
            ft_termcap_do("up");
}

void	ft_arrows(t_lin **lst)
{
	char	buf[5];

	if (read(0, buf, 5) > 0)
	{
		if (!ft_strncmp(buf, ARROW_UP, 2))
			ft_arrows_up(lst);
		else if (!ft_strncmp(buf, ARROW_DOWN, 2))
			ft_arrows_down(lst);
        else if (!ft_strncmp(buf, HOME, 2) && caret != 0)
            ft_home_cursor();
        else if (!ft_strncmp(buf, END, 2))
            ft_end_cursor();
        else if (!ft_strncmp(buf, DELETE, 3))
            ft_delete();
        else if (!ft_strncmp(buf, UP, 3))
            ft_cursor_up(size_colum(), line, caret);
        else if (!ft_strncmp(buf, DOWN, 3))
            ft_cursor_down(size_colum(), 0, -1, line, caret);
		else if (!ft_strncmp(buf, ARROW_LEFT, 2) && caret > 0)
		{
            if (line[caret - 1] == '\n')
            {
                ft_do_arrow(size_colum(), caret - 2);
                caret -= 2;
            }
            else
            {
                ft_do_arrow(size_colum(), caret - 1);
                caret--;
            }
		}
		else if (!ft_strncmp(buf, ARROW_RITE, 2) && caret < (int)ft_strlen((char*)line))
		{
            if (line[caret + 1] == '\n')
            {
                ft_do_arrow(size_colum(), caret + 2);
                caret += 2;
            }
            else
            {
                ft_do_arrow(size_colum(), caret + 1);
                caret++;
            }
        }
//		else if (!ft_str)
//		else if (buf[0] == 91 && buf[1] == 51 && buf[2] == 126) //? delete
	}
}
