/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/16 19:43:11 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/17 00:00:14 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_label					*getlabels(void)
{
	static t_label		labels = (t_label){0, NULL};

	if (labels.label == NULL)
		labels.label = ft_lstnew(NULL, 0);
	return (&labels);
}

void					print_label(void)
{
	t_label				*label = getlabels();

	t_list				*labels = label->label;
	while (labels)
	{
		printf("content: %10s\tsize: %zu\n", labels->content, labels->content_size);
		labels = labels->next;
	}
}

int						label_index(char *name)
{
	t_list				*labels;
	int					index;

	index = 0;
	labels = getlabels()->label;
	while (labels)
	{
		if (labels->content)
			if (!ft_strcmp(labels->content, name))
				return (index);
		index++;
		labels = labels->next;
	}
	return (-1);
}

int						label_value(char *name, int index)
{
	t_list				*labels;

	labels = getlabels()->label;
	while (labels)
	{
		printf("%s == %s\n", name, labels->content);
		if (labels->content)
			if (!ft_strcmp(labels->content, name))
				return (labels->content_size - index);
		labels = labels->next;
	}
	return (INT_MAX);
}

int						add_label(char *name, int value)
{
	t_list				*new_labels;
	t_list				*labels;

	if (name)
	{
		if (label_index(name) != -1)
			return (1);
		new_labels = ft_lstnew(name, ft_strlen(name) + 1);
	}
	else
		new_labels = ft_lstnew(NULL, 0);
	new_labels->content_size = value;
	labels = getlabels()->label;
	ft_lstaddback(&labels, new_labels);
	return (0);
}

int						skip_header(int input, t_token *token)
{
	unsigned int		i;
	
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
		while ((*token = lexer(input)).type != (t_types){Newline})
			if (token->type != (t_types){Whitespace})
				return (4);
		i++;
	}
	return (0);
}

t_arg				peek_arg(int input, t_token *token, int opcode)
{
	t_arg			arg;
	int				sign;

	arg = (t_arg){-1, -1, -1};
	while (token->type == (t_types){Whitespace})
		*token = lexer(input);;
	if (token->type == (t_types){Symbol})
	{
		if (*(token->str) == DIRECT_CHAR)
		{
			*token = lexer(input);
			if (token->type == (t_types){Symbol})
			{
				if (*(token->str) == '+' || *(token->str) == '-')
				{
					sign = (*(token->str) == '+') ? 1 : -1;
					*token = lexer(input);
					if (token->type == (t_types){Number})
						arg = (t_arg){T_DIR, sign * ft_atoi(token->str), (op_tab[opcode].label) ? DIR_SIZE / 2 : DIR_SIZE};
				}
				else if (*(token->str) == LABEL_CHAR)
				{
					*token = lexer(input);
					arg = (t_arg){T_DIR, 0, (op_tab[opcode].label) ? DIR_SIZE / 2 : DIR_SIZE};
				}
			}
			else if (token->type == (t_types){Number})
				arg = (t_arg){T_DIR, ft_atoi(token->str), (op_tab[opcode].label) ? DIR_SIZE / 2 : DIR_SIZE};
		}
		else if (*(token->str) == '+' || *(token->str) == '-')
		{
			sign = (*(token->str) == '+') ? 1 : -1;
			*token = lexer(input);
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

static int			peek_opcode(int input, int *value, t_token *token, int opcode)
{
	int				i;
	t_arg			arg[3];

	i = 0;
	*token = lexer(input);
	*value += 1;
	while (i < op_tab[opcode].nb_arg)
	{
		if (i && token->type == (t_types){Symbol} && *(token->str) == SEPARATOR_CHAR)
			*token = lexer(input);
		else if (i)
			return (2);
		if ((arg[i] = peek_arg(input, token, opcode)).size == -1)
			return (1);
		if (!(op_tab[opcode].args[i] & arg[i].type))
			return (3);
		i++;
	}
	int j = -1;
	if (op_tab[opcode].octal)
		*value += 1;
	while (++j < i)
		*value += arg[j].size;
	return (0);
}

int					init_label(int input, int *value)
{
	t_token			token;

	*value = 0;
	if (skip_header(input, &token))
		return (1);
	while (token.type != (t_types){None})
	{
		while (token.type == (t_types){Whitespace}
		|| token.type == (t_types){Newline})
			token = lexer(input);
		if (token.type == (t_types){Label})
		{
			if (add_label(token.str, *value))
				return (2);
			if ((token = lexer(input)).type != (t_types){Symbol} || *(token.str) != LABEL_CHAR)
				return (3);
			token = lexer(input);
		}
		else if (token.type == (t_types){Keyword})
		{
			if (peek_opcode(input, value, &token, ft_getkeyword(token.str)))
					return (6);
			while (token.type != (t_types){Newline})
			{
				if (token.type != (t_types){Whitespace})
					return (7);
				token = lexer(input);
			}
		}
		else if (token.type == (t_types){None})
			break ;
		else
			printf("ERROR\n");
	}
	lseek(input, 0, SEEK_SET);
	print_label();
	return (0);
}