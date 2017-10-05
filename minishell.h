#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <dirent.h>

typedef struct		s_lin
{
	char			*lin;
	struct s_lin	*next;
	struct s_lin	*prev;
}					t_lin;

char				**ft_init_env(char **env);
char				**ft_unsetenv(char **env, char *str);
void				ft_dell_arrey(char **tmp);
int					ft_arrey_size(char **tmp);
int					ft_search_line_env(char **env, char *str);
char				**ft_setenv(char **env, char *str, char *src);
char				*call_binary(char **my_env, char *name);
char				**ft_cd(char **env, char *arg);
void				ft_echo(char **env, char *arg);

#endif
