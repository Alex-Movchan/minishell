#include "minishell.h"

void    set_term(struct termios standart)
{
    struct termios new_settings;


    new_settings = standart;
    new_settings.c_lflag &= (~ICANON & ~ECHO);
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);
}
void    reset_term(struct termios *standart)
{
    tcsetattr(0,TCSANOW, standart);
}

int		main(int ac, char **av, char **env)
{
	int				i;
	char			**m_env;
    struct termios  standart;
	char			*line;
	t_lin			*lst;

	lst = NULL;
	tcgetattr(0, &standart);
	m_env = ft_init_env(env);
	set_term(standart);
	do_monishell(m_env);
    reset_term(&standart);
	return (0);
}