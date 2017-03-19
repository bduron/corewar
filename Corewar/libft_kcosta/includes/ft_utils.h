/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 17:13:35 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/03 11:11:38 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_H
# define FT_UTILS_H

# ifndef HEX
#  define HEX "0123456789abcdef"
# endif

# ifndef BUFF_SIZE
#  define BUFF_SIZE 1024
# endif

# include <unistd.h>
# include <string.h>
# include <stdlib.h>

int		ft_atoi(const char *str);
char	*ft_itoa(int n);

int		ft_getopt(int argc, char **argv,
									const char *ft_optstring, int *ft_optind);
int		ft_getline(const int fd, char **line);

#endif
