#include "minishell.h"

int		ft_term_putchar(int c)
{
	if (write(STDIN_FILENO, &c, 1) != 1)
		return (0);
	return (1);
}

void	ft_termcap_do(char *flag)
{
	char	*str;

	if ((str = tgetstr(flag, NULL)) != NULL)
		write(2, str, ft_strlen(str));
}
