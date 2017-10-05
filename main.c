#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	int		i;
	char	**m_env;

	m_env = ft_init_env(env);
	i = -1;
	ft_unsetenv(m_env, "HOME");
//	if (ac >1)
		m_env = ft_cd(m_env, av[1]);
	while (m_env[++i])
		printf("%s\n", m_env[i]);
	return (0);
}