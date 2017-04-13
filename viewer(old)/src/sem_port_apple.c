/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_port_apple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:49:25 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/12 18:52:17 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sem_port.h"
#ifdef __APPLE__

void	sem_port_init(t_sem_port *s, uint32_t value)
{
	dispatch_semaphore_t *sem;

	sem = &s->sem;
	*sem = dispatch_semaphore_create(value);
}

void	sem_port_wait(t_sem_port *s)
{
	dispatch_semaphore_wait(s->sem, DISPATCH_TIME_FOREVER);
}

void	sem_port_post(t_sem_port *s)
{
	dispatch_semaphore_signal(s->sem);
}

#endif
