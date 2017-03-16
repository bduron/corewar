/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:07:41 by kcosta            #+#    #+#             */
/*   Updated: 2017/03/16 16:05:29 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char				*ft_stradd(char **str, char c)
{
	char		*tmp;
	char		dup[2];

	dup[0] = c;
	dup[1] = 0;
	if (!str)
		return (NULL);
	if (!*str)
		return (ft_strdup(dup));
	tmp = *str;
	*str = ft_strjoin(*str, dup);
	ft_strdel(&tmp);
	return (*str);
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
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

t_token					lexer(int fd)
{
	t_token				token;
	static t_character	chr = {0, 0, 0, 0};
	
	chr = (chr.cargo) ? chr : scanner(fd);
	token = (t_token){0, 0, 0, 0};
	while (ft_strchr(WHITESPACE_CHARS, chr.cargo) || chr.cargo == COMMENT_CHAR)
	{
		while (ft_strchr(WHITESPACE_CHARS, chr.cargo))
		{
			token = (t_token){ft_stradd(&(token.cargo), chr.cargo),
						chr.line_index, chr.col_index, (t_types){Whitespace}};
			chr = scanner(fd);
			while (ft_strchr(WHITESPACE_CHARS, chr.cargo))
			{
				token.cargo = ft_stradd(&(token.cargo), chr.cargo);
				chr = scanner(fd);
			}
			return (token);
		}
		while (chr.cargo == COMMENT_CHAR)
		{
			token = (t_token){ft_stradd(&(token.cargo), chr.cargo),
						chr.line_index, chr.col_index, (t_types){Comment}};
			chr = scanner(fd);
			while (chr.cargo != '\n')
			{
				if (chr.cargo == 0)
					return (token);
				token.cargo = ft_stradd(&(token.cargo), chr.cargo);
				chr = scanner(fd);
			}
			return (token);
		}
	}
	if (ft_strchr(SYMBOL_CHARS, chr.cargo))
	{
		token = (t_token){ft_stradd(&(token.cargo), chr.cargo),
					chr.line_index, chr.col_index, (t_types){Symbol}};
		chr = scanner(fd);
		return (token);
	}
	if (ft_strchr(LABEL_CHARS, chr.cargo))
	{
		token = (t_token){ft_stradd(&(token.cargo), chr.cargo),
					chr.line_index, chr.col_index, (t_types){Label}};
		chr = scanner(fd);
		while (ft_strchr(LABEL_CHARS, chr.cargo))
		{
			token.cargo = ft_stradd(&(token.cargo), chr.cargo);
			chr = scanner(fd);
		}
		if (ft_iskeyword(token.cargo))
			token.type = (t_types){Keyword};
		else if (ft_strisdigit(token.cargo))
			token.type = (t_types){Number};
		return (token);
	}
	if (chr.cargo == '"')
	{
		token = (t_token){ft_stradd(&(token.cargo), chr.cargo),
					chr.line_index, chr.col_index, (t_types){String}};
		chr = scanner(fd);
		while (chr.cargo != '"')
		{
			if (chr.cargo == 0)
				return (token);
			token.cargo = ft_stradd(&(token.cargo), chr.cargo);
			chr = scanner(fd);
		}
		token.cargo = ft_stradd(&(token.cargo), chr.cargo);
		chr = scanner(fd);
		return (token);
	}
	return (token);
}

int					main(int argc, char **argv)
{
	char			*str_type[11] = {"None", "Whitespace", "Label", "Keyword", "Comment", "Symbol", "String", "Number"};
	t_token			token;
	int				fd;

	token = (t_token){0, 0, 0, 0};
	if (argc != 2)
		return (1);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (2);
	while (1)
	{
		if (token.cargo)
			ft_strdel(&(token.cargo));
		token = lexer(fd);
		printf("%5d\t%5d\t%10s\t%s\n", token.line_index, token.col_index, str_type[token.type], token.cargo);
		if (token.type == (t_types){None})
			return (0);
	}
}
