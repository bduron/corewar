/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:07:41 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/17 13:24:05 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token			ft_tokenupdate(t_token token, t_types type, char chr)
{
	unsigned int		index;

	token.type = type;
	index = ft_strlen(token.str);
	if (index < COMMENT_LENGTH)
		token.str[ft_strlen(token.str)] = chr;
	return (token);
}

static int				ft_iskeyword(char *word)
{
	int					i;

	i = 0;
	while (op_tab[i].name)
	{
		if (!(ft_strcmp(op_tab[i].name, word)))
			return (1);
		i++;
	}
	return (0);
}

int						ft_strisdigit(char *str)
{
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static int				ft_isregister(char *word)
{
	int		value;

	if (*word != 'r')
		return (0);
	if (!ft_strisdigit(word + 1))
		return (0);
	value = ft_atoi(word + 1);
	if (value > 16 || value <= 0)
		return (0);
	return (1);
}

static char				lexer_manage_white(t_token *token, char chr, int fd)
{
	while (ft_strchr(WHITESPACE_CHARS, chr) || chr == COMMENT_CHAR)
	{
		while (ft_strchr(WHITESPACE_CHARS, chr))
		{
			token->type = (t_types){Whitespace};
			while (ft_strchr(WHITESPACE_CHARS, chr))
			{
				if (chr == '\n')
					token->type = (t_types){Newline};
				chr = scanner(fd);
			}
		}
		while (chr == COMMENT_CHAR)
		{
			token->type = (t_types){Comment};
			while (chr != '\n')
			{
				if (chr == 0)
					return (0);
				chr = scanner(fd);
			}
		}
	}
	return (chr);
}

static char				lexer_manage_label(t_token *token, char chr, int fd)
{
	*token = ft_tokenupdate(*token, (t_types){Label}, chr);
	chr = scanner(fd);
	while (ft_strchr(LABEL_CHARS, chr))
	{
		*token = ft_tokenupdate(*token, token->type, chr);
		chr = scanner(fd);
	}
	if (chr == LABEL_CHAR)
		;
	else if (ft_iskeyword(token->str))
		token->type = (t_types){Keyword};
	else if (ft_strisdigit(token->str))
		token->type = (t_types){Number};
	else if (ft_isregister(token->str))
		token->type = (t_types){Register};
	return (chr);
}

static char				lexer_manage_string(t_token *token, char chr, int fd)
{
	token->type = (t_types){String};
	chr = scanner(fd);
	while (chr != '"')
	{
		if (chr == 0)
			return (0);
		*token = ft_tokenupdate(*token, token->type, chr);
		chr = scanner(fd);
	}
	chr = scanner(fd);
	return (chr);
}

t_token					lexer(int fd)
{
	t_token				token;
	static char			chr = -1;

	chr = (chr != -1) ? chr : scanner(fd);
	token = (t_token){0, 0};
	ft_memset(token.str, 0, COMMENT_LENGTH + 1);
	if (ft_strchr(WHITESPACE_CHARS, chr) || chr == COMMENT_CHAR)
		chr = lexer_manage_white(&token, chr, fd);
	else if (ft_strchr(SYMBOL_CHARS, chr))
	{
		token = ft_tokenupdate(token, (t_types){Symbol}, chr);
		chr = scanner(fd);
	}
	else if (chr == '"')
		chr = lexer_manage_string(&token, chr, fd);
	else if (ft_strchr(LABEL_CHARS, chr))
		chr = lexer_manage_label(&token, chr, fd);
	return (token);
}
