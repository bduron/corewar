/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 14:57:13 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/14 17:21:35 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <string.h>
# include <stdlib.h>

size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

char	*ft_strcpy(char *dst, const char *src);
char	*ft_strncpy(char *dst, const char *src, size_t len);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strncat(char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *big, const char *little);
char	*ft_strrstr(const char *big, const char *little);
char	*ft_strnstr(const char *big, const char *little, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strequ(const char *s1, const char *s2);
int		ft_strnequ(const char *s1, const char *s2, size_t n);

char	*ft_strnew(size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strinsert(char **str, char c, size_t index);
char	*ft_strremove(char **str, size_t index);
char	*ft_strsub(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
void	ft_strclr(char *s);
void	ft_strdel(char **as);
void	ft_strswp(char **s1, char **s2);

char	*ft_strrev(char *s);
char	*ft_strtrim(const char *s);
char	*ft_strepur(const char *s);

void	ft_striter(char *s, void (*f)(char*));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(const char *s, char (*f)(char));
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));

char	**ft_strsplit(const char *s, char c);

int		ft_strisalnum(const char *s);

#endif
