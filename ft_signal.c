#include "minishell.h"

void	ft_hendler_kill(int sig)
{
	if (sig == SIGINT)
	{
		if (pid != 0)
        {
            kill(pid, SIGINT);
            ft_putchar('\n');
        }
        else
		{
			ft_putstr("\n$>");
			caret = 0;
			if (line[0] != '\0')
				ft_bzero((void*)line, ft_strlen((char*)line));
		}
		ft_signal();
	}

}

void	ft_signal()
{
	signal(SIGINT, ft_hendler_kill);
    signal(SIGCHLD, SIG_IGN);
}
