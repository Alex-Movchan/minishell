#include "minishell.h"

int     ft_add_vertical(int size_len, int *horisontal, int size)
{
    int     i;
    int     len;
    int     count;
    
    i = -1;
    count = 0;
    len = -1;
    while (++i <= size)
    {
        len++;
        if (line[i] == '\n' ||(line[i + 1] != '\0' &&
            ((count == 0 && len + 2 == size_len) ||
            (count && len >= size_len && len % size_len == 0))))
        {
            count++;
            len = line[i] == '\n' ? -1 : 0;
        }
    }
    if (count == 0)
        *horisontal = len + 2 == size_len ? len - 1 : len;
    else
        *horisontal = len  % size_len == 0 ? len - 1 : len;
    *horisontal = *horisontal == -1 ? 0 : *horisontal;
    return (count);
}

void    offset_cursor(int horisontal, int vertical)
{
    if (vertical)
    {
        if (horisontal > 2)
            while(horisontal-- > 2)
                ft_termcap_do("le");
        else if (horisontal < 2)
            while (horisontal++ < 2)
                ft_termcap_do("nd");
    }
    else
        while(horisontal--)
            ft_termcap_do("le");
    while (--vertical >= 0)
        ft_termcap_do("up");
}

void    ft_return_cursor(int size_line, int len, int dup, char *str)
{
    int     v1;
    int     v2;
    int     h1;
    int     h2;
    
    v1 = ft_add_vertical(size_line, &h1, caret);
    v2 = ft_add_vertical(size_line, &h2, len);
    offset_cursor(h2 - h1, v2 - v1);
}

void    ft_home_cursor()
{
    int     vertical;
    int     horizontal;
    int     size_line;
    int     flag;
    
    flag = 0;
    size_line = size_colum();
    vertical = ft_add_vertical(size_line, &horizontal, caret);
    offset_cursor(horizontal, vertical);
    caret = 0;
}

void    ft_end_cursor()
{
    int     i;
    
    i = (int)ft_strlen((char*)line);
    if (i == caret)
        return;
    ft_home_cursor();
    ft_termcap_do("cd");
    ft_putstr(line);
    caret = i;
}

void    ft_clearline()
{
    int     dup_caret;
    
    dup_caret = caret;
    ft_home_cursor();
    caret = dup_caret;
    ft_termcap_do("cd");
}



