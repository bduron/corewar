/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:37:20 by kcosta            #+#    #+#             */
/*   Updated: 2017/03/14 16:46:53 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCANNER_H
# define SCANNER_H

# include <fcntl.h>
# include <stdio.h>
# include "libft.h"

typedef struct		s_character
{
	char			cargo;
	unsigned short	source_index;
	unsigned short	line_index;
	unsigned short	col_index;
}					t_character;

t_character			scanner(int fd);

#endif
