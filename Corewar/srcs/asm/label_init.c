/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 16:53:23 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/18 17:01:25 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		init_skip_whitespace(int input, t_token *token)
{
	while (token->type == (t_types){Whitespace}
	|| token->type == (t_types){Newline})
		*token = lexer(input);
	return (0);
}

static int		init_manage_label(int input, t_token *token, int *value)
{
	if (add_label(token->str, *value))
		return (1);
	if ((*token = lexer(input)).type != (t_types){Symbol}
		|| *(token->str) != LABEL_CHAR)
		return (2);
	*token = lexer(input);
	return (0);
}

static int		init_manage_opcode(int input, t_token *token, int *value)
{
	if (peek_opcode(input, value, token, ft_getkeyword(token->str)))
		return (1);
	while (token->type != (t_types){Newline})
	{
		if (token->type != (t_types){Whitespace})
			return (2);
		*token = lexer(input);
	}
	return (0);
}

int				init_label(int input, int *value)
{
	t_token			token;

	*value = 0;
	if (skip_header(input, &token))
		return (1);
	while (token.type != (t_types){None})
	{
		init_skip_whitespace(input, &token);
		if (token.type == (t_types){Label})
		{
			if (init_manage_label(input, &token, value))
				return (2);
		}
		else if (token.type == (t_types){Keyword})
		{
			if (init_manage_opcode(input, &token, value))
				return (3);
		}
		else if (token.type == (t_types){None})
			break ;
		else
			return (1);
	}
	lseek(input, 0, SEEK_SET);
	return (0);
}
