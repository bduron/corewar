/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:52:23 by kcosta            #+#    #+#             */
/*   Updated: 2017/03/16 16:02:57 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scanner.h"

/*int					main(int argc, char **argv)
{
	t_character		character;
	int				fd;
	if (argc != 2)
		return (1);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (2);
	while (1)
	{
		character = scanner(fd);
		printf("%5d\t%5d\t%5d\t%c\n", character.source_index, character.line_index, character.col_index, character.cargo);
		if (character.cargo == 0)
			return (0);
	}
}*/

t_character		scanner(int fd)
{
	static unsigned short	source_index = -1;
	static unsigned short	line_index = 0;
	static unsigned short	col_index = -1;
	static char				c = 0;
	t_character				character;

	source_index++;
	if (c == '\n')
	{
		line_index++;
		col_index = -1;
	}
	col_index++;
	if (read(fd, &c, 1) > 0)
		character = (t_character){c, source_index, line_index, col_index};
	else
		character = (t_character){-1, source_index, line_index, col_index};
	return (character);
}
