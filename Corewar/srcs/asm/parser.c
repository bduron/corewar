/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:55:22 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/17 00:24:22 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char					*str_type[10] = {"None", "Comment", "Whitespace", "Newline", "Label", "Keyword", "Register", "Symbol", "String", "Number"};

int						ft_getkeyword(char *word)
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

static unsigned int		reverse_byte_32(unsigned int num)
{
	unsigned int		reverse;

	reverse = 0x000000FF & num;
	reverse = (reverse << 8) + ((0x0000FF00 & num) >> 8);
	reverse = (reverse << 8) + ((0x00FF0000 & num) >> 16);
	reverse = (reverse << 8) + ((0xFF000000 & num) >> 24);
	return (reverse);
}

static unsigned short	reverse_byte_16(unsigned int num)
{
	unsigned short		reverse;

	reverse = 0x00FF & num;
	reverse = (reverse << 8) + ((0xFF00 & num) >> 8);
	return (reverse);
}

ssize_t					fixed_write(int fildes, const void *buf, size_t nbyte)
{
	unsigned int		fixed;

	if (nbyte == 4)
		fixed = reverse_byte_32(*(unsigned int*)buf);
	else if (nbyte == 2)
		fixed = reverse_byte_16(*(unsigned int*)buf);
	else
		fixed = *(unsigned int*)buf;
	return (write (fildes, &fixed, nbyte));
}

static int				parse_header(int input, int output, t_token *token, int *value) // Need to check if name.length > PROG_NAME_LENGTH and if comment.length > COMMENT_LENGTH
{
	unsigned int		i;
	
	i = COREWAR_EXEC_MAGIC;
	fixed_write (output, &i, sizeof(i));
	i = 0;
	while (i < 2)
	{
		*token = lexer(input);
		printf("%10s\t%s\n", str_type[token->type], token->str);
		if (token->type != (t_types){Symbol} || *(token->str) != '.')
			return (1);
		*token = lexer(input);
		printf("%10s\t%s\n", str_type[token->type], token->str);
		if (token->type != (t_types){Label}
		|| ft_strcmp(token->str, (i == 0) ? "name" : "comment"))
			return (2);
		while ((*token = lexer(input)).type == (t_types){Whitespace})
			;
		if (token->type != (t_types){String})
			return (3);
		if (i)
			fixed_write (output, value, sizeof(i));
		write (output, token->str, i == 0 ? PROG_NAME_LENGTH + 4 : COMMENT_LENGTH + 4); // Must be a clean write here we copy garbage char // Dont know why the +4 (Maybe I miss a int somewhere ?)
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
	while (token->type == (t_types){Whitespace})
		*token = lexer(input);
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
					if (label_index(token->str) != -1)
					{
						printf("\tvalue:\t%d\n", label_value(token->str, getlabels()->index));
						arg = (t_arg){T_DIR, label_value(token->str, getlabels()->index), (op_tab[opcode].label) ? DIR_SIZE / 2 : DIR_SIZE};
					}
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

static int			parse_opcode(int input, int output, t_token *token, int opcode)
{
	int				i;
	int				par;
	t_arg			arg[3];

	par = 0;
	i = 0;
	printf("%10s\t%s\n", str_type[token->type], token->str);
	*token = lexer(input);
	fixed_write (output, &(op_tab[opcode].opcode), 1);
	while (i < op_tab[opcode].nb_arg)
	{
		if (i && token->type == (t_types){Symbol} && *(token->str) == SEPARATOR_CHAR)
			*token = lexer(input);
		else if (i)
			return (2);
		if ((arg[i] = parse_arg(input, token, opcode)).size == -1)
			return (1);
		if (!(op_tab[opcode].args[i] & arg[i].type))
			return (3);
		arg[i].type = (arg[i].type == T_IND) ? IND_CODE : arg[i].type;
//		printf("\tType:\t%10d\n", arg[i].type);
		par = (par << 2) + arg[i].type;
//		printf("\tParameter:\t%10.8p\n", par);
		i++;
	}
	int j = i;
	while (j++ < 4)
	{
		par = par << 2;
//		printf("\tParameter:\t%10.8p\n", par);
	}
	j = -1;
	if (op_tab[opcode].octal)
	{
		fixed_write (output, &par, 1);
		getlabels()->index += 1;
	}
	while (++j < i)
	{
		fixed_write (output, &(arg[j].value), arg[j].size);
		getlabels()->index += arg[j].size;
	}
	getlabels()->index += 1;
	return (0);
}

int					main(int argc, char **argv)
{
	t_token			token;
	int				input;
	int				output;
	int				value;

	if (argc != 2)
		return (1);
	if ((input = open(argv[1], O_RDONLY)) < 0)
		return (2);
	if ((output = open("test", O_CREAT | O_RDWR, 0644)) < 0)
		return (3);
	if (init_label(input, &value))
		return (-1);
	if (parse_header(input, output, &token, &value))
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
	return (0);
}