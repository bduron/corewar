/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 16:57:00 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/01 13:18:14 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINT_H
# define FT_PRINT_H

# ifndef HEX
#  define HEX	"0123456789abcdef"
# endif

# ifndef PRINTF_LENGTH
#  define PRINTF_LENGTH

#  define L_HH	0
#  define L_H	1
#  define L_L	2
#  define L_LL	3
#  define L_J	4
#  define L_Z	5

# endif

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <wchar.h>

typedef struct	s_flags
{
	int			hash;
	int			zero;
	int			minus;
	int			plus;
	int			space;
}				t_flags;

typedef struct	s_format
{
	t_flags		flags;
	int			width;
	int			precision;
	int			length;
	char		type;
}				t_format;

int				ft_printf(const char *format, ...);
int				ft_printf_format(va_list ap, const char **str, int *size);
int				ft_printf_flush_format(const char **str, t_format *format,
																	int *size);

int				ft_printf_print_arg(va_list ap, t_format *format, int *size);
int				ft_printf_print_num(va_list ap, t_format *format);
int				ft_printf_print_unsigned(va_list ap, t_format *format);
int				ft_printf_print_octal(va_list ap, t_format *format);
int				ft_printf_print_hex(va_list ap, t_format *format);
int				ft_printf_print_address(va_list ap, t_format *format);
int				ft_printf_print_str(va_list ap, t_format *format);
int				ft_printf_print_char(va_list ap, t_format *format);

int				ft_printf_pourcent(t_format *format);
int				ft_printf_hex(uintmax_t nb, t_format *format);
void			ft_get_width(va_list ap, const char **str, t_format *format);

int				ft_printf_isflag(int c);
int				ft_printf_islength(int c);
int				ft_printf_istype(int c);

int				ft_wcharlen(wint_t c);
void			ft_putwchar(wint_t c);

void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);

void			ft_putstr(const char *s);
void			ft_putstr_fd(const char *s, int fd);

void			ft_putendl(const char *s);
void			ft_putendl_fd(const char *s, int fd);

void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);

ssize_t			ft_putnstr(const char *str, size_t len);

#endif
