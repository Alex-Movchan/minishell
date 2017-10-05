#include "minishell.h"

static char	*print_d_name(char *name, int flag)
{
	
}

static char	*search_comand(char **tmp, char *line, size_t len)
{
	int				i;
	DIR				*ptr;
	struct dirent	*dir;

	i = -1;
	while (tmp[++i])
	{
		if (!(ptr = opendir(tmp[i])))
			continue ;
		while ((dir = readdir(ptr)))
		{
			if (!ft_strncmp(dir->d_name, line, len))
			{

			}
		}
	}
}

char	*auto_completion(char *line, char **env)
{
	int		i;
	char	*comand;
	char	**tmp;

	i = ft_search_line_env(env, "PATH");
	if (i == ft_arrey_size(env))
		return (line);
	tmp = ft_strsplit(env[i] + 5, ':');

}