/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:42:08 by bduron            #+#    #+#             */
/*   Updated: 2017/03/09 17:34:31 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_LIBFT_H
# define H_LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdint.h>

# define BUFF_SIZE 1
# define MAXV 100000

typedef enum
{
	FALSE,
	TRUE
}	t_bool;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_edgenode
{
	int					y;
	int					weight;
	char				*name;
	struct s_edgenode	*next;

}				t_edgenode;

typedef struct	s_bfs
{
	t_list		*queue;
	int			v;
	int			*pop;
	int			y;
	t_edgenode	*p;

}				t_bfs;

typedef struct	s_graph
{
	struct s_edgenode	*edges[MAXV + 1];
	int					degree[MAXV + 1];
	int					nvertices;
	int					nedges;
	t_bool				directed;
	int					bfs_parent[MAXV + 1];
	t_bool				bfs_processed[MAXV + 1];
	t_bool				bfs_discovered[MAXV + 1];
}				t_graph;

void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putnbr(int n);
size_t			ft_strlen(const char *s);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
long			ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strdup(const char *s1);
char			*ft_strcat(char *restrict s1, const char *restrict s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *big, const char *little);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *big, const char *little, size_t len);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
void			ft_strsplitdel(char **split);
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
void			ft_striter(char *s, void (*f)(char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char(*f)(unsigned int, char));
char			*ft_itoa(int n);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(char const *s);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstaddback(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			*ft_lstpop(t_list **alst);
void			ft_lstpush(t_list **alst, t_list *new);
void			ft_lstappend(t_list **alst, t_list *new);
int				ft_lstlen(t_list *alst);
int				*ft_lstinttab(t_list *alst);
int				ft_islower(int c);
int				ft_isupper(int c);
void			ft_squeeze(char *s, int c);
void			ft_strrev(char *s);
int				ft_isspace(int c);
int				ft_isdigitstr(char *s);
int				get_next_line(int fd, char **line);
int				ft_printf(const char *format, ...);
int				ft_getline(const int fd, char **line);

/*
** Graph functions
*/

void			initialize_graph(t_graph *g, t_bool directed);
void			insert_edge(t_graph *g, int x, int y, t_bool directed);
void			print_graph(t_graph *g, char **label);
void			initialize_bfs(t_graph *g);
void			bfs_norme(t_graph *g, int start, t_bfs *b);
void			process_vertex_late(int v);
void			process_vertex_early(int v);
void			process_edge(int v, int y);
void			find_path_rec(int start, int end, int *parents);
t_list			*find_path_bfs(int start, int end, int *parents);

#endif
