#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <dirent.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>
#include <termcap.h>
# include <sys/ioctl.h>


#define ARROW_UP  "[A"
#define ARROW_DOWN "[B"
#define ARROW_LEFT "[D"
#define ARROW_RITE "[C"
#define HOME "[H"
#define END "[F"
#define UP "[5~"
#define DOWN "[6~"
#define DELETE "[3~"


#define MAX_LINE_SIZE 1024

typedef struct		s_lin
{
	char			*line;
	int				flag;
	int				caret;
	struct s_lin	*next;
	struct s_lin	*prev;
}					t_lin;

typedef struct		s_file
{
    char			*name;
    struct s_file	*next;
}					t_file;

typedef	struct		s_term
{
	char			**env;
    char            *term;
	char			*odpwd;
	char			*home;
	struct termios  canon;
	struct termios  not_canon;
}					t_term;

extern char			line[MAX_LINE_SIZE];
extern int	    	caret;
extern pid_t        pid;

void        ft_env(char **arg, t_term *term);
char				**ft_unsetenv(char **env, char **arg);
void	            ft_signal(void);
void				ft_dell_arrey(char **tmp);
int					ft_arrey_size(char **tmp);
int					ft_search_line_env(char **env, char *str);
char				**ft_setenv(char **env, char *str, char *src);
char				*call_binary(char **my_env, char *name);
char		**ft_cd(char **env, char **arg, t_term **term);
void				ft_echo(char **env, char *arg);
void				add_alpha_file(t_file **begin, t_file *file);
t_file				*ft_search_comand(char *line, char **env);
t_file				*ft_search_file(char *lin, int len, t_file *begin);
void				auto_completion(t_term *term, char *c);
t_file				*get_file(char **env, int *i);
void				ft_arrows(t_lin **lst);
void			read_line(t_lin **lst, t_term *term);
void				ft_back_print(size_t len);
char				*ft_search_d_name(char **name, int *len);
void				do_monishell(t_term *term);
char				**ft_linesplit(void);
void				ft_termcap_do(char *flag);
char				**ft_strsplit_quot(char *str);
int                 size_colum(void);
void                ft_clearline(void);
void    ft_return_cursor(int size_line, int len, int dup, char *str);

//void                ft_return_cursor(int size_line, int len);
int                 ft_add_vertical(int size_len, int *horisontal, int size);
void                ft_home_cursor(void);
void                ft_end_cursor(void);
void                ft_delete(void);
//void                ft_cursor_up(int size_len);
void     ft_cursor_up(int size_len, char *str, int dup);

void     ft_cursor_down(int size_len, int count, int len_caret, char *str, int dup);
//void              ft_cursor_down(int size_len, int count, int len_caret, int len_next)



#endif
