#include "minishell.h"

void    ft_mov_up(int len_prev, int len_caret, int count, int size_len)
{
    int shift;
    
    ft_termcap_do("up");
    if (count == 1 && len_caret <= 2)
    {
        while (len_caret++ <= 2)
            ft_termcap_do("nd");
        caret = 0;
    }
    else if (len_prev < len_caret)
    {
        shift = len_caret - len_prev;
        caret -= len_caret;
        while (shift--)
            ft_termcap_do("le");
    }
    else
        caret = count == 1 ?  caret - (len_prev + 2) : caret - len_prev;
}

void     ft_cursor_up(int size_len, char *str, int dup)
{
    int     i;
    int     prev_len;
    int     len;
    int     count;

    i = -1;
    count = 0;
    len = 0;
    prev_len = 0;
    while (++i <= caret)
    {
        len++;
        if ((line[i] == '\n' && i != caret) ||(line[i + 1] != '\0' &&
           ((count == 0 && len + 1 == size_len) ||
           (count && len == size_len))))
        {
            count++;
            prev_len = len;
            len = 0;
        }
    }
    if (count)
        ft_mov_up(prev_len, len, count, size_len);
    dup = caret;
}

void    ft_mov_down(int pos_caret, int len_caret, int len_next, int count)
{
    int shift;
    
    ft_termcap_do("do");
    if (pos_caret > len_next)
        caret += (len_caret - pos_caret + 1);
    else
        caret += len_caret;
    if (count == 2)
    {
        shift = 2;
        while (shift-- && len_next)
        {
            ft_termcap_do("nd");
            caret++;
            len_next--;
        }
    }
    if (len_next == 1 && pos_caret)
    {
        ft_termcap_do("nd");
        caret++;
    }
    while (--pos_caret && --len_next)
    {
        caret++;
        ft_termcap_do("nd");
    }
    shift = caret;
}

void     ft_cursor_down(int size_len, int count, int len_caret, char *str, int dup)
{
    int i;
    int len;
    int pos_caret;
    
    i = -1;
    len = 0;
    pos_caret = 0;
    while (str[++i])
    {
        len++;
        if (i == caret)
            pos_caret = len;
        if (line[i] == '\n' ||(line[i + 1] != '\0' &&
            ((count == 0 && len + 2 == size_len) ||
             (count && len == size_len))))
        {
            count++;
            if (i >= caret && len_caret >= 0)
                break ;
            else if (i >= caret)
                len_caret = len;
            len = 0;
        }
    }
    if (count == 2 && len && line[i] == '\0')
        count++;
    if (len_caret >= 0)
        return (ft_mov_down(pos_caret, len_caret, len, count));
}
