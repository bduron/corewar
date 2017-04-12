/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 15:25:59 by pboutelo          #+#    #+#             */
/*   Updated: 2017/03/16 09:21:19 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_fd_buff	*get_fd_buff(t_list **start, int fd)
{
	t_list		*lfb;
	t_fd_buff	new;

	lfb = *start;
	while (lfb)
	{
		if (((t_fd_buff *)lfb->content)->fd == fd)
		{
			return (lfb->content);
		}
		lfb = lfb->next;
	}
	new.buff = ft_strnew(BUFF_SIZE);
	new.fd = fd;
	ft_lstpushfront(start, &new, sizeof(t_fd_buff));
	return ((*start)->content);
}

static int			free_buff(t_list **start, int fd)
{
	t_list *prev;
	t_list *curr;

	curr = *start;
	prev = curr;
	while (curr)
	{
		if (((t_fd_buff *)curr->content)->fd == fd)
		{
			free(((t_fd_buff *)curr->content)->buff);
			if (curr == prev)
				*start = curr->next;
			else
				prev->next = curr->next;
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}

static int			read_from_buff(t_fd_buff **fd_buff, char **line)
{
	char	*next;
	int		r;
	int		i;

	r = ft_strlen((*fd_buff)->buff);
	*line = ft_strdup((*fd_buff)->buff);
	next = ft_strchr((*fd_buff)->buff, '\n');
	if (next)
	{
		i = next - (*fd_buff)->buff;
		while (i++ < r)
			(*line)[i - 1] = 0;
		ft_memmove((*fd_buff)->buff, next + 1, ft_strlen(next));
		return (1);
	}
	return (0);
}

static int			ft_get_next_line_sub(t_fd_buff *fb, int r, char **line)
{
	char	*cpy;
	char	*next;
	int		i;

	cpy = ft_strdup(*line);
	free(*line);
	*line = ft_strjoin(cpy, fb->buff);
	next = ft_strchr(fb->buff, '\n');
	if (next)
	{
		i = next - fb->buff;
		while (i++ < r)
			(*line)[ft_strlen(cpy) - 1 + i] = 0;
		ft_memmove(fb->buff, next + 1, ft_strlen(next));
		free(cpy);
		return (1);
	}
	else
		ft_bzero(fb->buff, BUFF_SIZE);
	free(cpy);
	return (0);
}

int					ft_get_next_line(const int fd, char **line)
{
	static t_list		*start = 0;
	int					r;
	int					flag;
	t_fd_buff			*fb;

	if (fd < 0 || !line)
		return (-1);
	fb = get_fd_buff(&start, fd);
	if (!read_from_buff(&fb, line))
	{
		flag = *fb->buff ? 1 : 0;
		ft_bzero(fb->buff, BUFF_SIZE);
		while ((r = read(fd, fb->buff, BUFF_SIZE)))
		{
			flag = 1;
			if (r == -1)
				return (r);
			if (ft_get_next_line_sub(fb, r, line))
				return (1);
		}
		return ((flag) ? 1 : free_buff(&start, fd));
	}
	else
		return (1);
}
