/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_port.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:38:05 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/12 18:36:49 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEM_PORT_H
# define SEM_PORT_H
# ifdef __APPLE__
#  include <dispatch/dispatch.h>
# else
#  include <semaphore.h>
# endif

typedef struct				s_sem_port
{
# ifdef __APPLE__

	dispatch_semaphore_t	sem;
# else

	sem_t					sem;
# endif

}							t_sem_port;

void						sem_port_init(t_sem_port *s, uint32_t value);
void						sem_port_wait(t_sem_port *s);
void						sem_port_post(t_sem_port *s);

#endif
