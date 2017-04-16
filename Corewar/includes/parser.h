/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:55:28 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/16 23:49:51 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <fcntl.h>

# include "libft.h"
# include "op.h"
# include "scanner.h"
# include "lexer.h"

typedef struct		s_arg
{
	char			type;
	int				value;
	int				size;
}					t_arg;

typedef struct		s_label
{
	int				index;
	t_list			*label;
}					t_label;


t_label				*getlabels(void);

int					ft_getkeyword(char *word);
int					init_label(int input, int *value);
int					label_index(char *name);
int					label_value(char *name, int index);

#endif
