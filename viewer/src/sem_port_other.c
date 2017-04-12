/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_port_other.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:49:25 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/12 18:09:13 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sem_port.h"
#ifndef __APPLE__

void	sem_port_init(t_sem_port *s, uint32_t value)
{
	sem_init(&s->sem, 0, value);
}

void	sem_port_wait(t_sem_port *s)
{
	int r;

	r = sem_wait(&s->sem);
	while (r == -1 && errno == EINTR)
		r = sem_wait(&s->sem);
}

void	sem_port_post(t_sem_port *s)
{
	sem_post(&s->sem);
}

#endif
