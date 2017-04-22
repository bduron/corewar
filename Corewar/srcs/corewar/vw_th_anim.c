/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vw_th_anim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 16:25:09 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/22 18:53:34 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "viewer.h"

static void	th_anim_run(t_viewer *v, int i, int step)
{
	if (step % 2)
		wattron(v->win_champions[i], A_BOLD);
	else
		wattroff(v->win_champions[i], A_BOLD);
	draw_life_full(v, i);
	wrefresh(v->win_champions[i]);
}

void		*th_anim_routine(void *p_data)
{
	t_anim		*a;
	int			step;

	a = (t_anim *)p_data;
	step = 8;
	pthread_mutex_lock(&a->v->mutex);
	werase(a->v->win_champions[a->i]);
	wattron(a->v->win_champions[a->i], COLOR_PAIR(a->i + 2));
	pthread_mutex_unlock(&a->v->mutex);
	while (step--)
	{
		pthread_mutex_lock(&a->v->mutex);
		th_anim_run(a->v, a->i, step);
		pthread_mutex_unlock(&a->v->mutex);
		usleep(70000);
	}
	pthread_mutex_lock(&a->v->mutex);
	wattroff(a->v->win_champions[a->i], A_BOLD);
	wattroff(a->v->win_champions[a->i], COLOR_PAIR(a->i + 2));
	a->v->anim_flags ^= 1 << a->i;
	// pthread_cond_broadcast(&a->v->cond);
	pthread_mutex_unlock(&a->v->mutex);
	free(a);
	pthread_exit(0);
}

void		*th_credits_routine(void *p_data)
{
	t_viewer *v;

	v = (t_viewer *)p_data;
	pthread_mutex_lock(&v->mutex);
	while (1)
	{
		if (v->event_flags)
			pthread_cond_wait(&v->cond, &v->mutex);
		else
		{
			show_credits(v);
			break ;
		}
	}
	pthread_mutex_unlock(&v->mutex);
	pthread_exit(0);
}
