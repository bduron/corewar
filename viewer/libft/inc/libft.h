/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:12:56 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/03 16:54:37 by wolrajhti        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 4098
# include <libc.h>
# include <wchar.h>

/*
**	libft
*/
void					*ft_memset(void *b, int c, size_t len);
void					ft_bzero(void *s, size_t n);
void					*ft_memcpy(void *dst, const void *src, size_t n);
void					*ft_memccpy(void *dst, const void *src, int c,
							size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
size_t					ft_strlen(const char *s);
char					*ft_strdup(const char *s1);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strncpy(char *dst, const char *src, size_t len);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strncat(char *s1, const char *s2, size_t n);
size_t					ft_strlcat(char *dst, const char *src, size_t size);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strstr(const char *big, const char *little);
char					*ft_strnstr(const char *big, const char *little,
							size_t len);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_atoi(const char *str);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isnumberstr(char *str);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);

void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s, char (*f)(unsigned int,
							char));
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strsub(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s);
char					**ft_strsplit(char const *s, char c);
char					*ft_itoa(int n);
void					ft_putchar(char c);
void					ft_putstr(char const *s);
void					ft_putendl(char const *s);
void					ft_putnbr(int n);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr_fd(int n, int fd);

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(t_list **alst,
							void (*del)(void *, size_t));
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

int						ft_isupper(int c);
int						ft_islower(int c);
void					ft_lstpushfront(t_list **alst, void const *content,
							size_t content_size);
void					ft_lstpushback(t_list **alst, void const *content,
							size_t content_size);
int						ft_lstsize(t_list *alst);
t_list					*ft_lstat(t_list *alst, unsigned int n);
t_list					*ft_lstlast(t_list *alst);
void					ft_lstreverse(t_list **alst);
void					ft_lstremif(t_list **begin_list, void *data_ref,
							int (*cmp)(), void (*del)(void *, size_t));

/*
**	ft_get_next_line
*/

typedef struct			s_fd_buff
{
	int					fd;
	char				*buff;
}						t_fd_buff;

int						ft_get_next_line(const int fd, char **line);

/*
**	ft_printf
*/

typedef struct			s_base
{
	char				charset[256];
	unsigned char		len;
}						t_base;

typedef struct			s_directive
{
	int					pos;
	int					len;
	int					na;
	char				na_arg;
	char				af;
	char				zp;
	char				la;
	char				as;
	char				pa;
	int					fl;
	char				fl_arg;
	int					p;
	char				p_arg;
	char				lm;
	char				cs;
	const t_base		*base;
	char				valid;
}						t_directive;

int						ft_printf(const char *format, ...);
int						parse_directive(const char *str, int *i, va_list args,
							int *na);
void					init_directive(t_directive *d, int *i,
							int *arg_position);
int						write_directive(t_directive *d, va_list cpy);
void					set_args(t_directive *d, va_list cpy);
void					set_base(t_directive *d);
int						parse_int(int *dest, const char *str, int *i);
int						parse_next_argument(t_directive *d, const char *str,
							int *i);
int						parse_flag(t_directive *d, const char *str, int *i);
int						parse_field_length(t_directive *d, const char *str,
							int *i);
int						parse_precision(t_directive *d, const char *str,
							int *i);
int						parse_length_modifier(t_directive *d, const char *str,
							int *i);
int						parse_conversion_specifier(t_directive *d,
							const char *str, int *i);
int						write_p(t_directive *d, va_list cpy);
int						write_x(t_directive *d, va_list cpy);
int						write_u(t_directive *d, va_list cpy);
int						write_di(t_directive *d, va_list cpy);
int						write_ob(t_directive *d, va_list cpy);
int						write_c(t_directive *d, va_list cpy);
int						write_s(t_directive *d, va_list cpy);
int						write_ls(t_directive *d, va_list cpy);
int						write_error(t_directive *d);
size_t					set_ustr(t_directive *d, char **str, va_list cpy);
size_t					set_str(t_directive *d, char **str, va_list cpy,
							char *is_negative);
unsigned long long		get_number(va_list cpy, int n);
int						write_loop(const char c, int n);
int						ft_wctomb(char *s, wchar_t wc);
size_t					ft_itoa_base(char **dest, unsigned long long src,
							const t_base *b);

#endif
