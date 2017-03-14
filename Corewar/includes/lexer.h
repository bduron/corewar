/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:07:55 by kcosta            #+#    #+#             */
/*   Updated: 2017/03/14 18:37:28 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "op.h"
# include "scanner.h"

typedef enum		e_types
{
	None,
	Whitespace,
	Label,
	Keyword,
	Comment,
	Separator,
	Register,
	Direct,
	Indirect,
	Name,
	Description
}					t_types;

typedef struct		s_token
{
	char			*cargo;
	unsigned short	line_index;
	unsigned short	col_index;
	t_types			type;
}					t_token;

t_token				lexel(int fd);

#endif
