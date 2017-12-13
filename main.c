#include "minishell.h"

int     caret;
char	line[MAX_LINE_SIZE];
pid_t   pid;


char	**ft_init_env(char **env, t_term **term)
{
	char	**tmp;
	int		i;
	int		size;

	size = ft_arrey_size(env);
	tmp = (char**)malloc(sizeof(char*) * size + 1);
	i = -1;
	while (++i < size)
	{
		tmp[i] = ft_strdup(env[i]);
		if (!ft_strncmp("HOME=", tmp[i], 5))
			(*term)->home = ft_strdup(tmp[i] + 5);
		else if (!ft_strncmp("OLDPWD=", tmp[i], 7))
			(*term)->odpwd = ft_strdup(tmp[i] + 7);
		else if (!ft_strncmp("TERM=", tmp[i], 5))
            (*term)->term = ft_strdup(tmp[i] + 5);

	}
	tmp[i] = NULL;
	return (tmp);
}

t_term	*initterm(char **env)
{
	t_term	*term;

	term = (t_term*)malloc(sizeof(t_term));
	term->term = NULL;
    term->home = NULL;
    term->odpwd = NULL;
    term->env = ft_init_env(env, &term);
    if (term->term)
        tgetent(NULL, term->term);
    else
    {
        ft_putstr_fd("\e[0;31mminishell: error search variable term\e[0m\n", 2);
        exit(1);
    }
	tcgetattr(0, &term->canon);
	term->not_canon = term->canon;
	term->not_canon.c_lflag &= (~ICANON & ~ECHO);
	term->not_canon.c_cc[VTIME] = 0;
	term->not_canon.c_cc[VMIN] = 1;
	return (term);
}

int		main(int ac, char **av, char **env)
{
    t_term	*term;

	if (ac != 1)
	{
		return (0);
	}
	pid = 0;
	term = initterm(env);
	ft_signal();
	do_monishell(term);
	return (0);
}
