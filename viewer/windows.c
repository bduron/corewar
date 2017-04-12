#include <libc.h>
#include <ncurses.h>
#include <pthread.h>
#include <errno.h>
//next are useless
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/select.h>

#ifdef __APPLE__
	#include <dispatch/dispatch.h>
#else
	#include <semaphore.h>
#endif

typedef struct					s_rk_sema
{
	#ifdef __APPLE__
		dispatch_semaphore_t	sem;
	#else
		sem_t					sem;
	#endif
}								t_rk_sema;

static inline void rk_sema_init(t_rk_sema *s, uint32_t value)
{
	#ifdef __APPLE__
		dispatch_semaphore_t *sem = &s->sem;
		*sem = dispatch_semaphore_create(value);
	#else
		sem_init(&s->sem, 0, value);
	#endif
}

static inline void rk_sema_wait(t_rk_sema *s)
{
	#ifdef __APPLE__
		dispatch_semaphore_wait(s->sem, DISPATCH_TIME_FOREVER);
	#else
		int r;
		do {
			r = sem_wait(&s->sem);
		} while (r == -1 && errno == EINTR);
	#endif
}

static inline void rk_sema_post(t_rk_sema *s)
{
	#ifdef __APPLE__
		dispatch_semaphore_signal(s->sem);
	#else
		sem_post(&s->sem);
	#endif
}

WINDOW *create_newwin(int height, int width, int starty, int startx, char *name);
void destroy_win(WINDOW *local_win);

typedef struct		s_viewer
{
	char			arena[1024];
	char			*names[4];
	char			events[4][100];
	WINDOW			*win_arena;
	WINDOW			*win_champions[4];
	WINDOW			*win_infos;
	t_rk_sema		sem_coreDone;
	t_rk_sema		sem_ready2core;
	t_rk_sema		sem_show;
	t_rk_sema		sem_pause;
	t_rk_sema		sem_sleepDone;
	t_rk_sema		sem_ready2sleep;
	char			flag_pause;
	int				step;
	int				input;
	struct timeval	tv;
}					t_viewer;

void *core(void * arg)
{
	t_viewer *v;
	int laps;
	int i;
	int counter;

	v = (t_viewer *)arg;
	laps = 100000;
	counter = v->step;
	while (laps--)
	{
		// ----------------------------
		// put the program logic here
		// ...
		++v->arena[laps % 1024];
		// ...
		// ...
		// ----------------------------
		// ----------------------------
		// then render specific frame here
		--counter;
		if (!counter)
		{
			i = -1;
			while (++i < 4)
			{
				bzero(v->events + i, 100);
				sprintf(v->events[i], "%d %s", 100000 - laps, v->names[i]);
			}
			rk_sema_post(&v->sem_coreDone);
			rk_sema_wait(&v->sem_ready2core);
			counter = v->step;
		}
		// ----------------------------
	}
	pthread_exit(0);
}

void *controls(void * arg)
{
	t_viewer	*v;
	int			i;

	v = (t_viewer *)arg;
	werase(v->win_infos);
	mvwprintw(v->win_infos, 2, 3, "recording one frame every %d laps.\t\t(edit width 'k' & 'l')", v->step);
	mvwprintw(v->win_infos, 3, 3, "actual speed is %d sec, %d usec.\t\t(edit width 'o' & 'p')", v->tv.tv_sec, v->tv.tv_usec);
	mvwprintw(v->win_infos, 4, 3, "Press 'q' to quit");
	wrefresh(v->win_infos);
	while(v->input != 'q' && v->input != 'Q')
	{
		if ((v->input = getch()) == ERR)
		{
			// stop_curses(&cinfo);
			// fprintf(stderr, "ERR returned from getch()\n");
			// pthread_exit(0);
		}
		else if (v->input == 'o')
		{
			v->tv.tv_usec /= 2;
			if (v->tv.tv_sec == 1)
				v->tv.tv_usec += 500000;
			v->tv.tv_sec /= 2;
		}
		else if (v->input == 'p')
		{
			v->tv.tv_sec *= 2;
			v->tv.tv_usec *= 2;
			if (v->tv.tv_usec > 999999)
			{
				v->tv.tv_sec += v->tv.tv_usec / 1000000;
				v->tv.tv_usec %= 1000000;
			}
		}
		else if (v->input == 'k')
		{
			if (v->step > 1)
				v->step /= 2;
		}
		else if (v->input == 'l')
		{
			if (v->step < 800)
				v->step *= 2;
		}
		else if (v->input == ' ')
		{
			if (!(v->flag_pause = !v->flag_pause))
				rk_sema_post(&v->sem_pause);
		}
		else if (v->input == 'q')
			break ;
		werase(v->win_infos);
		mvwprintw(v->win_infos, 2, 3, "recording one frame every %d laps.\t\t(edit width 'k' & 'l')", v->step);
		mvwprintw(v->win_infos, 3, 3, "actual speed is %d sec, %d usec.\t\t(edit width 'o' & 'p')", v->tv.tv_sec, v->tv.tv_usec);
		mvwprintw(v->win_infos, 4, 3, "Press 'q' to quit");
		mvwprintw(v->win_infos, 5, 3, v->flag_pause ? "PAUSE" : "");
		wrefresh(v->win_infos);
	}
	pthread_exit(0);
}

void *sleep_routine(void *arg)
{
	t_viewer	*v;
	int			i;

	v = (t_viewer *)arg;
	i = 0;
	while(v->input != 'q' && v->input != 'Q')
	{
		rk_sema_wait(&v->sem_ready2sleep);
		usleep(v->tv.tv_sec * 1000000 + v->tv.tv_usec);
		werase(v->win_arena);
		mvwprintw(v->win_arena, 2, 3, "%d", i++);
		wrefresh(v->win_arena);
		rk_sema_post(&v->sem_sleepDone);
	}
	pthread_exit(0);
}

void *show(void * arg)
{
	t_viewer *v;
	int i;
	int index;

	v = (t_viewer *)arg;

	while(v->input != 'q' && v->input != 'Q')
	{
		if (v->flag_pause)
			rk_sema_wait(&v->sem_pause);
		rk_sema_wait(&v->sem_coreDone);
		rk_sema_wait(&v->sem_sleepDone);
		i = -1;
		while (++i < 4)
		{
			werase(v->win_champions[i]);
			mvwprintw(v->win_champions[i], 0, 0, v->events[i]);
			wrefresh(v->win_champions[i]);
		}
		rk_sema_post(&v->sem_ready2core);
		rk_sema_post(&v->sem_ready2sleep);
	}
	pthread_exit(0);
}

int main(int argc, char *argv[])
{
	t_viewer	v;
	pthread_t	th_core, th_show, th_controls, th_sleep;
	void		*ret;
	int			i;

	v.names[0] = "Wolfgang junior";
	v.names[1] = "Mc Ron";
	v.names[2] = "Eude Herbert";
	v.names[3] = "Jacques-Henri";

	v.step = 40;
	v.tv.tv_sec = 1;
	v.tv.tv_usec = 0;
	v.flag_pause = 0;

	bzero(v.arena, 1024);

	rk_sema_init(&v.sem_ready2core, 0);
	rk_sema_init(&v.sem_ready2sleep, 1);
	rk_sema_init(&v.sem_coreDone, 0);
	rk_sema_init(&v.sem_sleepDone, 0);
	rk_sema_init(&v.sem_pause, 1);

	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	refresh();

	v.win_arena = create_newwin(32, (32 + 2) * 2, 0, 0, "Arena");
	i = -1;
	while (++i < 1024)
		mvwprintw(v.win_arena, i / 32, (i % 32) * 2, "%x", v.arena[i] % 256);
	wrefresh(v.win_arena);
	i = -1;
	while (++i < 4)
		v.win_champions[i] = create_newwin(LINES - 32, (32 + 2) * 2 / 4, 32, i * (32 + 2) * 2 / 4, v.names[i]);
	v.win_infos = create_newwin(LINES, COLS - (32 + 2) * 2, 0, (32 + 2) * 2, "Informations");

	// v.win_arena = create_newwin(LINES - 10, 2 * (LINES - 10), 0, 0, "Arena");
	// i = -1;
	// while (++i < 4096)
	// 	mvwprintw(v.win_arena, i / 64, (i % 64) * 2, "%x", i % 256);
	// wrefresh(v.win_arena);
	// i = -1;
	// while (++i < 4)
	// 	v.win_champions[i] = create_newwin(10, 2 * (LINES - 10) / 4, LINES - 10, i * 2 * (LINES - 10) / 4, v.names[i]);
	// v.win_infos = create_newwin(LINES, COLS - 2 * (LINES - 10), 0, 2 * (LINES - 10), "Informations");

	if (pthread_create(&th_core, NULL, &core, &v) < 0) {
	  fprintf(stderr, "pthread_create error for th_core\n");
	  exit(1);
	}

	if (pthread_create(&th_controls, NULL, &controls, &v) < 0) {
	  fprintf(stderr, "pthread_create error for th_controls\n");
	  exit(1);
	}

	if (pthread_create(&th_sleep, NULL, &sleep_routine, &v) < 0) {
	  fprintf(stderr, "pthread_create error for th_sleep\n");
	  exit(1);
	}

	if (pthread_create(&th_show, NULL, &show, &v) < 0) {
	  fprintf(stderr, "pthread_create error for th_show\n");
	  exit(1);
	}

	(void)pthread_join(th_core, &ret);
	(void)pthread_join(th_controls, &ret);
	(void)pthread_join(th_show, &ret);
	(void)pthread_join(th_sleep, &ret);

	endwin();

	return (0);
}

WINDOW *create_newwin(int height, int width, int starty, int startx, char *name)
{
	WINDOW *win_box;
	WINDOW *win_content;
	size_t	len;

	win_box = newwin(height, width, starty, startx);
	box(win_box, 0 , 0);
	win_content = derwin(win_box, height - 2, width - 4, 1, 2);
	len = strlen(name);
	wmove(win_box, 0, (width - len) / 2 - 3);
	wprintw(win_box, " - %s - ", name);
	wrefresh(win_box);
	wrefresh(win_content);
	return (win_content);
}
