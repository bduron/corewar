/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:14:44 by kcosta            #+#    #+#             */
/*   Updated: 2017/02/09 15:44:30 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "libft.h"

static int	ft_error(char *msg, int ft_errnum)
{
	ft_putendl_fd(msg, 2);
	return (ft_errnum);
}

static char	*ft_check_file(char *filename)
{
	char	*extension;
	char	*output;

	output = NULL;
	extension = ft_strchr(filename, '.');
	if (!extension)
		return (NULL);
	if (ft_strcmp(extension, ".s"))
		return (NULL);
	output = ft_strnew(extension - filename + 4);
	ft_strncpy(output, filename, extension - filename + 1);
	ft_strncpy(ft_strchr(output, '.') + 1, "cor", 3);
	return (output);
}

static int	ft_compile(char *in_name, char *out_name)
{
	int		input;
	int		output;

	if ((input = open(in_name, O_RDONLY)) < 0)
		return (1);
	if ((output = open(out_name, O_WRONLY | O_CREAT, 0644)) < 0)
		return (1);
	write(output, (int[4]){0x01, 0x02, 0x03, 0x04}, sizeof(int[4]));
	close(input);
	close(output);
	return (0);
}

int		main(int argc, char **argv)
{
	char	*output;

	if (argc != 2)
		return (ft_error("usage: ./asm champion.s", 1));
	if (!(output = ft_check_file(argv[1])))
		return (ft_error("Invalid file\nusage: ./asm champion.s", 1));
	if (ft_compile(argv[1], output))
		return (ft_error(strerror(errno), 2));
}
