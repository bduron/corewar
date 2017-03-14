/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 17:07:41 by kcosta            #+#    #+#             */
/*   Updated: 2017/03/14 19:20:06 by kcosta           ###   ########.fr       */
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
	chr = scanner(fd);
	return (token);
}

int					main(int argc, char **argv)
{
	char			*str_type[11] = {"None", "Whitespace", "Label", "Keyword", "Comment", "Separator", "Register", "Direct", "Indirect", "Name", "Description"};
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
