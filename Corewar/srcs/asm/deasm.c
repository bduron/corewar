/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deasm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 16:04:32 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/20 19:41:08 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

static int	rev_parse_header(int input, int output)
{
	char	c;
	int		index;
	int		i;
	char	*type;
	int		limit;

	i = -1;
	while (++i < 2)
	{
		index = 0;
		type = (i) ? ".comment \"" : ".name \"";
		limit = (i) ? COMMENT_LENGTH + 4 : PROG_NAME_LENGTH + 4;
		read(input, (char[4]){0}, 4);
		read(input, &c, 1);
		write(output, type, ft_strlen(type));
		while (++index < limit && c)
		{
			write(output, &c, 1);
			read(input, &c, 1);
		}
		write(output, "\"\n", ft_strlen("\"\n"));
		while (index++ < limit)
			read(input, &c, 1);
	}
	return (0);
}

static int	rev_parser_manage_octal(int input, int output, int opcode)
{
	int		args;
	int		nb;
	int		res;
	char	*str;

	nb = -1;
	read(input, &args, 4);
	while (++nb < g_op_tab[opcode].nb_arg)
	{
		write(output, g_op_tab[opcode].name, ft_strlen(g_op_tab[opcode].name));
		write(output, " ", 1);
		res = (args >> (6 - 2 * nb)) & 0b11;
		if (res == T_IND)
		{
			read(input, &res, IND_SIZE);
			str = ft_itoa(res);
			write(output, str, ft_strlen(str));
			ft_strdel(&str);
		}
		else if (res == T_DIR)
		{
			read(input, &res, g_op_tab[opcode].label ? DIR_SIZE / 2 : DIR_SIZE);
			write(output, "%", 1);
			str = ft_itoa(res);
			write(output, str, ft_strlen(str));
			ft_strdel(&str);
		}
		else
		{
			read(input, &res, 1);
			write(output, "r", 1);
			str = ft_itoa(res);
			write(output, str, ft_strlen(str));
			ft_strdel(&str);
		}
		if (nb < g_op_tab[opcode].nb_arg - 1)
			write(output, ", ", 1);
	}
	write(output, "\n", 1);
	return (0);
}

static int	rev_parser_manage_other(int input, int output, int opcode)
{
	int		nb;
	int		res;
	char	*str;

	nb = -1;
	while (++nb < g_op_tab[opcode].nb_arg)
	{
		write(output, g_op_tab[opcode].name, ft_strlen(g_op_tab[opcode].name));
		write(output, " ", 1);
		if (g_op_tab[opcode].args[nb] == T_IND)
		{
			read(input, &res, IND_SIZE);
			str = ft_itoa(res);
			write(output, str, ft_strlen(str));
			ft_strdel(&str);
		}
		else if (g_op_tab[opcode].args[nb] == T_DIR)
		{
			read(input, &res, g_op_tab[opcode].label ? DIR_SIZE / 2 : DIR_SIZE);
			write(output, "%", 1);
			str = ft_itoa(res);
			write(output, str, ft_strlen(str));
			ft_strdel(&str);
		}
		else
		{
			read(input, &res, 1);
			write(output, "r", 1);
			str = ft_itoa(res);
			write(output, str, ft_strlen(str));
			ft_strdel(&str);
		}
		if (nb < g_op_tab[opcode].nb_arg - 1)
			write(output, ", ", 1);
	}
	return (0);
}

static int	rev_parser(int input, int output)
{
	int		opcode;
	char	code;

	write(output, "\n", 1);
	while (read(input, &code, 1) > 0)
	{
		opcode = code - 1;
		printf("%d\n", code);
		if (g_op_tab[opcode].octal)
			rev_parser_manage_octal(input, output, opcode);
		else
			rev_parser_manage_other(input, output, opcode);
		write(output, "\n", 1);
	}
	return (0);
}

int			ft_decompile(char *input_name, char *output_name)
{
	int		input;
	int		output;

	if ((input = open(input_name, O_RDONLY)) < 0)
		return (ft_error("Can't read source file", 1));
	if ((output = open(output_name, O_CREAT | O_RDWR, 0644)) < 0)
		return (2);
	rev_parse_header(input, output);
	rev_parser(input, output);
	return (0);
}
