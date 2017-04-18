/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:14:44 by kcosta            #+#    #+#             */
/*   Updated: 2017/04/18 17:01:18 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*ft_check_file(char *filename)
{
	char	*extension;
	char	*output;

	output = NULL;
	extension = ft_strrchr(filename, '.');
	if (!extension)
		return (NULL);
	if (ft_strcmp(extension, ".s"))
		return (NULL);
	output = ft_strnew(extension - filename + 4);
	ft_strncpy(output, filename, extension - filename + 1);
	ft_strncpy(ft_strrchr(output, '.') + 1, "cor", 3);
	return (output);
}

int				main(int argc, char **argv)
{
	char	*output;
	int		ret;

	if (argc != 2)
		return (ft_error("usage: ./asm champion.s", 1));
	if (!(output = ft_check_file(argv[1])))
		return (ft_error("Invalid file\nusage: ./asm champion.s", 1));
	if ((ret = ft_compile(argv[1], output)))
		return (ft_error("Error during compilation", ret));
}
