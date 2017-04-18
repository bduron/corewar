/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:37:20 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/18 18:30:21 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include <stdlib.h>

# include "lexer.h"

typedef struct		s_char
{
	char			c;
	int				col;
	int				line;
}					t_char;

ssize_t				fixed_write(int fildes, const void *buf, size_t nbyte);
int					lexical_error(t_token token, int ft_errnum);

t_char				scanner(int fd);

#endif
