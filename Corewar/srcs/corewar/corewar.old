/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:15:08 by kcosta            #+#    #+#             */
/*   Updated: 2017/02/11 13:13:49 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"
#include "libft.h"

int				regs[ REG_NUMBER ];
unsigned int	pc = 0;
unsigned char	carry = 1;
int				cycle = 10;

static int		ft_error(char *msg, int ft_errnum)
{
	ft_putendl_fd(msg, 2);
	return (ft_errnum);
}

static int		ft_check_file(char *filename)
{
	int		fd;
	char	*extension;

	extension = ft_strchr(filename, '.');
	if (!extension)
		return (ft_error("Invalid file\nusage: ./corewar champion.cor", -1));
	if (ft_strcmp(extension, ".cor"))
		return (ft_error("Invalid file\nusage: ./corewar champion.cor", -1));
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (ft_error(strerror(errno), -1));
	return (fd);
}

static int		fetch(int fd)
{
	int			instr;
	int			ret;
	
	ret = read(fd, &instr, sizeof(int));
	if (ret < 0)
		return (ft_error(strerror(errno), -1));
	if (ret < 4)
	{
		lseek(fd, 0, SEEK_SET);
		read(fd, &instr, sizeof(int));
		pc = 0;
	}
	pc++;
	return (instr);
}

static void		eval(int instr)
{
	if (instr == 1)
	{
		ft_putstr("Command 1\n");
		return ;
	}
	else if (instr == 2)
	{
		ft_putstr("Command 2\n");
		return ;
	}
	else if (instr == 3)
	{
		ft_putstr("Command 3\n");
		return ;
	}
	else if (instr == 4)
	{
		ft_putstr("Command 4\n");
		return ;
	}
	(void)ft_error("Unknown Command", 1);
}

int				main(int argc, char **argv)
{
	int			fd;
	int			instr;

	if (argc != 2)
		return (ft_error("usage: ./corewar champion.cor", 1));
	if ((fd = ft_check_file(argv[1])) == -1)
		return (2);
	while (carry)
	{
		if ((instr = fetch(fd)) == -1)
			return (3);
		eval(instr);
		if (!--cycle)
			carry = 0;
	}
	return (0);
}
