/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 13:55:28 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/15 22:53:15 by kcosta           ###   ########.fr       */
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

#endif
