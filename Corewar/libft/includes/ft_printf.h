/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 10:18:22 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 10:52:30 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_FT_PRINTF_H
# define H_FT_PRINTF_H

# include "libft.h"
# include <string.h>
# include <stdarg.h>
# define BUFSIZE 4096
# define HEX_L "0123456789abcdef"
# define HEX_U "0123456789ABCDEF"
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RES	"\x1B[0m"

typedef struct	s_flags
{
	int		flags[256];
	int		mod[256];
	char	str[256];
	int		width;
	int		precision;
	va_list	ap;
	size_t	plen;
	char	id;
	char	sign;
	int		s_bool;
	int		h_bool;
}				t_flags;

int				ft_printf(const char *format, ...);
void			fmt(t_flags *f, const char *format);
char			*get_flags(char *flag, t_flags *f);
int				is_flag(char c);
int				is_id(char id);
void			reset_flags(t_flags *f);
int				is_mod(char c);
void			launch_conv(t_flags *f);
void			conv_d(t_flags *f);
void			put_d(t_flags *f, char *s, int len);
int				count_digits(int nb);
int				max(int x, int y, int z);
long long		get_arg_u(t_flags *f);
long long		get_arg(t_flags *f);
void			conv_d(t_flags *f);
int				is_x(t_flags *f);
void			put_c(t_flags *f);
void			put_s(t_flags *f);
void			put_s_maj(t_flags *f);
void			conv_u(t_flags *f);
char			*get_wildcards(t_flags *f, char *s);
void			put_percent(t_flags *f);
void			launch_conv_digits(t_flags *f);
void			launch_conv_strings(t_flags *f);
void			launch_conv_unsigned(t_flags *f);
size_t			rem(size_t len, wchar_t *s);
size_t			ft_wlen(wchar_t s);
int				ft_printf_atoi(const char *str);
char			*ft_printf_itoa(uintmax_t n);
int				ft_putwchar(wchar_t c);
int				isnt_id(t_flags *f);
int				pad(int len, char c);

#endif
