#include "minishell.h"

static void	ft_now_line(char *line, t_lin **lin)
{
	t_lin	*now;

	now = (t_lin*)malloc(sizeof(t_lin));
	if (line)
		now->line = ft_strdup(line);
	else
		now->line = NULL;
	now->flag = 1;
	now->prev = NULL;
	now->next = *lin;
	(*lin)->prev = now;
}

static char	*ft_arrows_up(t_lin **lin, char *line)
{

	if (*lin)
	{
		if (!(*lin)->prev && (*lin)->flag != 1)
			ft_now_line(line, lin);
		if (line)
		{
			ft_back_print(ft_strlen(line));
			ft_strdel(&line);
		}
		line = ft_strdup((*lin)->line);
		ft_putstr(line);
		if ((*lin)->next)
			*lin = (*lin)->next;
	}
	return (line);
}

static char	*ft_arrows_down(t_lin **lin, char *line)
{
	if (*lin && (*lin)->prev)
	{
		if (line)
		{
			ft_back_print(ft_strlen(line));
			ft_strdel(&line);
		}
		line = ft_strdup((*lin)->prev->line);
		ft_putstr(line);
		if ((*lin)->prev)
			*lin = (*lin)->prev;
	}
	return (line);
}

char	*ft_arrows(t_lin **lst, char *line)
{
	char	buf[5];

	if (read(0, buf, 5) > 0)
	{
		if (!ft_strncmp(buf, ARROW_UP, 2))
			return (ft_arrows_up(lst, line));
		else if (!ft_strncmp(buf, ARROW_DOWN, 2))
			return (ft_arrows_down(lst, line));
//		else if (!ft_str)
		///else if (buf[0] == 91 && buf[1] == 51 && buf[2] == 126) //? delete
	}
	return (line);
}