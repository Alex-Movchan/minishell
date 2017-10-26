#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <dirent.h>
#include <termios.h>
#include <fcntl.h>
#include <termcap.h>

#define ARROW_UP  "[A"
#define ARROW_DOWN "[B"

typedef struct		s_lin
{
	char			*line;
	int				flag;
	struct s_lin	*next;
	struct s_lin	*prev;
}					t_lin;

typedef struct		s_file
{
    char			*name;
    struct s_file	*next;
}					t_file;

char				**ft_init_env(char **env);
char				**ft_unsetenv(char **env, char *str);
void				ft_dell_arrey(char **tmp);
int					ft_arrey_size(char **tmp);
int					ft_search_line_env(char **env, char *str);
char				**ft_setenv(char **env, char *str, char *src);
char				*call_binary(char **my_env, char *name);
char				**ft_cd(char **env, char *arg);
void				ft_echo(char **env, char *arg);
void				add_alpha_file(t_file **begin, t_file *file);
t_file				*ft_search_comand(char *line, char **env);
t_file				*ft_search_file(char *lin, int len, t_file *begin);
char				*auto_completion(char **env, char *line, char *c);
char				*ft_strchrrev(char *ctr, char c);
t_file				*get_file(char *str, char **env);
char				*ft_arrows(t_lin **lst, char *line);
char				*read_line(char **env, t_lin **lst);
void				ft_back_print(size_t len);
char				*ft_search_d_name(char **name, int *len);
void				do_monishell(char **env);

#endif
