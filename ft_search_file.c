#include "minishell.h"

static t_file	*ft_init_file(struct dirent *dir, t_file **begin)
{
	t_file	*file;

	file = (t_file*)malloc(sizeof(t_file));
	file->name = ft_strdup(dir->d_name);
	file->next = NULL;
	add_alpha_file(begin, file);
	return (*begin);
}

static t_file	*search_comand(char **tmp, char *line, size_t len, t_file *begin)
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
            begin = ft_init_file(dir, &begin);
		}
		closedir(ptr);
	}
	return (begin);
}

t_file			*ft_search_file(char *lin, int len, t_file *begin)
{
	char			*d_name;
	char			*f_name;
	DIR				*ptr;
	struct dirent	*dir;

	f_name = ft_strdup(lin);
	if (!ft_strchr(lin, '/') || !(d_name = ft_search_d_name(&f_name, &len)))
		d_name = ft_strdup(".");
	if (!(ptr = opendir(d_name)))
		return (NULL);
	while ((dir = readdir(ptr)) != NULL)
	{
		if (f_name[0] != '.' && dir->d_name[0] == '.')
			continue ;
		if (!ft_strncmp(f_name, dir->d_name, (size_t)len))
			begin = ft_init_file(dir, &begin);
	}
	closedir(ptr);
	ft_strdel(&d_name);
	ft_strdel(&f_name);
	return (begin);
}

t_file			*ft_search_comand(char *line, char **env)
{
	int		i;
	char	**tmp;
	t_file	*file;
	char	*str;

	str = line;
	while (*str && *str < 33)
		str++;
	i = ft_search_line_env(env, "PATH");
	if (i == ft_arrey_size(env))
		return (NULL);
	tmp = ft_strsplit(env[i] + 5, ':');
	if (!(file = search_comand(tmp, str, ft_strlen(str), NULL)))
	{
		ft_dell_arrey(tmp);
		return (NULL);
	}
	ft_dell_arrey(tmp);
	return (file);
}
