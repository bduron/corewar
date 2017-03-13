/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 10:48:59 by kcosta            #+#    #+#             */
/*   Updated: 2017/02/17 20:01:38 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_utils.h"

int		ft_getopt(int argc, char **argv,
									const char *ft_optstring, int *ft_optind)
{
	static int	ft_optarg = 1;

	if (*ft_optind < argc && argv[*ft_optind][0] == '-')
	{
		if (ft_optarg != 1 && !argv[*ft_optind][ft_optarg])
		{
			ft_optarg = 1;
			(*ft_optind)++;
			return (ft_getopt(argc, argv, ft_optstring, ft_optind));
		}
		if (!ft_strchr(ft_optstring, argv[*ft_optind][ft_optarg]))
		{
			if (!ft_strcmp(argv[*ft_optind], "--"))
			{
				(*ft_optind)++;
				return (-1);
			}
			return (argv[*ft_optind][ft_optarg]);
		}
		else
			return (argv[*ft_optind][ft_optarg++]);
	}
	return (-1);
}
