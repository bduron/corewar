/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:07:55 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/18 17:01:03 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define WHITESPACE_CHARS		"\t\n\v\f\r "
# define SYMBOL_CHARS			"#:%,.-+"

typedef enum		e_types
{
	None,
	Comment,
	Whitespace,
	Newline,
	Label,
	Keyword,
	Register,
	Symbol,
	String,
	Number
}					t_types;

typedef struct		s_token
{
	char			str[COMMENT_LENGTH + 1];
	t_types			type;
}					t_token;

t_token				lexer(int fd);

#endif
