/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:55:22 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/16 00:32:06 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char					*str_type[10] = {"None", "Comment", "Whitespace", "Newline", "Label", "Keyword", "Register", "Symbol", "String", "Number"};

static int				ft_getkeyword(char *word)
{
	int					i;

	i = 0;
	while (op_tab[i].name)
	{
		if (!(ft_strcmp(op_tab[i].name, word)))
			return (i);
		i++;
	}
	return (-1);
}

static int				parse_header(int input, int output, t_token *token) // Need to check if name.length > PROG_NAME_LENGTH and if comment.length > COMMENT_LENGTH
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

t_arg				parse_arg(int input, t_token *token, int opcode)
{
	t_arg			arg;
	int				sign;

	arg = (t_arg){-1, -1, -1};
	while ((*token = lexer(input)).type == (t_types){Whitespace})
		;
	printf("%10s\t%s\n", str_type[token->type], token->str);
	if (token->type == (t_types){Symbol})
	{
		if (*(token->str) == DIRECT_CHAR)
		{
			*token = lexer(input);
			printf("%10s\t%s\n", str_type[token->type], token->str);
			if (token->type == (t_types){Symbol})
			{
				if (*(token->str) == '+' || *(token->str) == '-')
				{
					sign = (*(token->str) == '+') ? 1 : -1;
					*token = lexer(input);
					printf("%10s\t%s\n", str_type[token->type], token->str);
					if (token->type == (t_types){Number})
						arg = (t_arg){T_DIR, sign * ft_atoi(token->str), (op_tab[opcode].label) ? DIR_SIZE / 2 : DIR_SIZE};
				}
				else if (*(token->str) == LABEL_CHAR)
				{
					*token = lexer(input);
					printf("%10s\t%s\n", str_type[token->type], token->str);
					if (1)
						arg = (t_arg){T_DIR, 0, (op_tab[opcode].label) ? DIR_SIZE / 2 : DIR_SIZE}; // Get value for label right
				}
			}
			else if (token->type == (t_types){Number})
				arg = (t_arg){T_DIR, ft_atoi(token->str), (op_tab[opcode].label) ? DIR_SIZE / 2 : DIR_SIZE};
		}
		else if (*(token->str) == '+' || *(token->str) == '-')
		{
			sign = (*(token->str) == '+') ? 1 : -1;
			*token = lexer(input);
			printf("%10s\t%s\n", str_type[token->type], token->str);
			if (token->type == (t_types){Number})
				arg = (t_arg){T_IND, sign * ft_atoi(token->str), IND_SIZE};
		}
	}
	else if (token->type == (t_types){Number})
		arg = (t_arg){T_IND, ft_atoi(token->str), IND_SIZE};
	else if (token->type == (t_types){Register})
		arg = (t_arg){T_REG, ft_atoi(token->str + 1), 1};
	while ((*token = lexer(input)).type == (t_types){Whitespace})
		;
	return (arg);
}

int					parse_opcode(int input, int output, t_token *token, int opcode)
{
	int				i;
	int				par;
	t_arg			arg[3];

	par = 0;
	i = 0;
	printf("%10s\t%s\n", str_type[token->type], token->str);
	while (i < op_tab[opcode].nb_arg)
	{
		*token = lexer(input);
		if ((arg[i] = parse_arg(input, token, opcode)).size == -1)
			return (1);
		par = (par << 1) + arg[i].type;
		i++;
	}
	return (0);
}

int					main(int argc, char **argv)
{
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
			printf("%10s\t%s\n", str_type[token.type], token.str);
			if ((token = lexer(input)).type != (t_types){Symbol} || *(token.str) != LABEL_CHAR)
				return (5);
			token = lexer(input);
		}
		else if (token.type == (t_types){Keyword})
		{
			if (parse_opcode(input, output, &token, ft_getkeyword(token.str)))
					return (6);
			while (token.type != (t_types){Newline})
			{
				if (token.type != (t_types){Whitespace})
					return (7);
				token = lexer(input);
			}
		}
		else if (token.type == (t_types){None})
			return (8);
		else
			printf("ERROR\n");
	}
}