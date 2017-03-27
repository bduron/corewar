/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:07:55 by kcosta            #+#    #+#             */
/*   Updated: 2017/03/27 18:56:05 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "op.h"
# include "scanner.h"

# define WHITESPACE_CHARS		"\t\n\v\f\r "
# define SYMBOL_CHARS			"#:%,.-+"

typedef enum		e_types
{
	None,
	Whitespace,
	Label,
	Keyword,
	Register,
	Comment,
	Symbol,
	String,
	Number
}					t_types;

/*
typedef struct		s_token
{
	char			*cargo;
	unsigned short	line_index;
	unsigned short	col_index;
	t_types			type;
}					t_token;
*/

typedef struct		s_token
{
	char			*str;
	t_types			type;
}					t_token;

t_token				lexer(int fd);

#endif
