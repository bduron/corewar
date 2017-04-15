/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:55:22 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/15 19:59:43 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int					parse_header(int input, int output, t_token *token) // Need to check if name.length > PROG_NAME_LENGTH and if comment.length > COMMENT_LENGTH
{
	int i = COREWAR_EXEC_MAGIC;

	write (output, &i, sizeof(i)); // Write backward
	i = 0;
	while (i < 2)
	{
		*token = lexer(input);
		if (token->type != (t_types){Symbol} || *(token->str) != '.')
			return (1);
		*token = lexer(input);
		if (token->type != (t_types){Label}
		|| ft_strcmp(token->str, (i == 0) ? "name" : "comment"))
			return (2);
		while ((*token = lexer(input)).type == (t_types){Whitespace})
			;
		if (token->type != (t_types){String})
			return (3);
		write (output, token->str, i == 0 ? PROG_NAME_LENGTH : COMMENT_LENGTH); // Must be a clean write here we copy garbage char
		while ((*token = lexer(input)).type != (t_types){Newline})
			if (token->type != (t_types){Whitespace})
				return (4);
		i++;
	}
	return (0);
}

int					main(int argc, char **argv)
{
	char			*str_type[10] = {"None", "Comment", "Whitespace", "Newline", "Label", "Keyword", "Register", "Symbol", "String", "Number"};
	t_token			token;
	int				input;
	int				output;

	if (argc != 2)
		return (1);
	if ((input = open(argv[1], O_RDONLY)) < 0)
		return (2);
	if ((output = open("test", O_CREAT | O_RDWR, 0644)) < 0)
		return (3);
	if (parse_header(input, output, &token))
		return (4);
	while (token.type != (t_types){None})
	{
		while (token.type == (t_types){Whitespace}
		|| token.type == (t_types){Newline})
			token = lexer(input);
		if (token.type == (t_types){Label})
		{
			if ((token = lexer(input)).type != (t_types){Symbol} || *(token.str) != LABEL_CHAR)
				return (5);
			token = lexer(input);
		}
		else if (token.type == (t_types){Keyword})
		{
			printf("%10s\t%s\n", str_type[token.type], token.str);
			while ((token = lexer(input)).type != (t_types){Newline})
				if (token.type == (t_types){None})
					return (6);
		}
		else if (token.type == (t_types){None})
			return (7);
		else
			printf("ERROR\n");
	}
}