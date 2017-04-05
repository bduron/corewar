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
#include <time.h>
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

typedef struct	s_viewer
{
	char		*names[4];
	char		events[4][100];
	WINDOW		*win_arena;
	WINDOW		*win_champions[4];
	WINDOW		*win_infos;
	t_rk_sema	sem_ready2core;
	t_rk_sema	sem_ready2show;
	int			step;
}				t_viewer;

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
			rk_sema_post(&v->sem_ready2show);
			rk_sema_wait(&v->sem_ready2core);
			counter = v->step;
		}
		// ----------------------------
	}
	pthread_exit(0);
}

void *show(void * arg)
{
	t_viewer *v;
	int ch;
	int i;
	int index;

	int input;
	struct timeval tv;
	// int secs = 0;
	// int usecs = 500000;
	int secs = 1;
	int usecs = 0;

	v = (t_viewer *)arg;
	initscr();
	keypad(stdscr, TRUE);
	timeout(0);
	cbreak();
	// raw();
	// nonl();
	noecho();
	refresh();
	v->win_arena = create_newwin(LINES - 10, 2 * (LINES - 10), 0, 0, "Arena");
	i = -1;
	while (++i < 4)
		v->win_champions[i] = create_newwin(10, 2 * (LINES - 10) / 4, LINES - 10, i * 2 * (LINES - 10) / 4, v->names[i]);
	v->win_infos = create_newwin(LINES, COLS - 2 * (LINES - 10), 0, 2 * (LINES - 10), "Informations");

	tv.tv_sec = secs;
	tv.tv_usec = usecs;

	while(input != 'q' && input != 'Q')
	{
		werase(v->win_infos);
		mvwprintw(v->win_infos, 2, 3, "recording one frame every %d laps.\t\t(edit width 'k' & 'l')", v->step);
		mvwprintw(v->win_infos, 3, 3, "actual speed is %d sec, %d usec.\t\t(edit width 'o' & 'p')", tv.tv_sec, tv.tv_usec);
		mvwprintw(v->win_infos, 4, 3, "Press 'q' to quit");
		wrefresh(v->win_infos);

		rk_sema_wait(&v->sem_ready2show);

		i = -1;
		while (++i < 4)
		{
			werase(v->win_champions[i]);
			mvwprintw(v->win_champions[i], 0, 0, v->events[i]);
			wrefresh(v->win_champions[i]);
		}
		rk_sema_post(&v->sem_ready2core);

		fd_set fds;
		FD_ZERO(&fds);
		FD_SET(STDIN_FILENO, &fds);

		int status = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);

        /*  Check for error  */

        if ( status == -1 ) {

            /*  select() returned with an error.  */

            if ( errno != EINTR ) {

                /*  If interrupted by a signal, no problem,
                 *  keep going. Otherwise, let's just quit.  */

                // stop_curses(&cinfo);
                perror("error calling select()");
                pthread_exit(0);
            }
        }
        else if ( FD_ISSET(STDIN_FILENO, &fds) ) {
            /*  Only call getch() if input is ready.
             *  getch() will not block when we do it this way.  */
            if ( (input = getch()) == ERR ) {
                // stop_curses(&cinfo);
                fprintf(stderr, "ERR returned from getch()\n");
                pthread_exit(0);
            }
			else if (input == 'o')
			{
				tv.tv_usec /= 2;
				if (tv.tv_sec == 1)
					tv.tv_usec += 500000;
				tv.tv_sec /= 2;
			}
			else if (input == 'p')
			{
				tv.tv_sec *= 2;
				tv.tv_usec *= 2;
				if (tv.tv_usec > 999999)
				{
					tv.tv_sec += tv.tv_usec / 1000000;
					tv.tv_usec %= 1000000;
				}
			}
			else if (input == 'k')
			{
				if (v->step > 1)
					v->step /= 2;
			}
			else if (input == 'l')
			{
				if (v->step < 800)
					v->step *= 2;
			}
        }
	}
	endwin();
	pthread_exit(0);
}

// void *show(void * arg)
// {
// 	t_viewer *v;
// 	int ch;
// 	int i;
// 	int index;
//
// 	v = (t_viewer *)arg;
// 	initscr();
// 	cbreak();
// 	keypad(stdscr, TRUE);
// 	noecho();
// 	refresh();
// 	v->win_arena = create_newwin(LINES - 10, 2 * (LINES - 10), 0, 0, "Arena");
// 	i = -1;
// 	while (++i < 4)
// 		v->win_champions[i] = create_newwin(10, 2 * (LINES - 10) / 4, LINES - 10, i * 2 * (LINES - 10) / 4, v->names[i]);
// 	v->win_infos = create_newwin(LINES, COLS - 2 * (LINES - 10), 0, 2 * (LINES - 10), "Informations");
// 	while(1)
// 	{
// 		rk_sema_wait(&v->sem_ready2show);
// 		i = -1;
// 		while (++i < 4)
// 		{
// 			werase(v->win_champions[i]);
// 			mvwprintw(v->win_champions[i], 0, 0, v->events[i]);
// 			wrefresh(v->win_champions[i]);
// 		}
// 		rk_sema_post(&v->sem_ready2core);
// 		sleep(1);
// 	}
// 	endwin();
// 	pthread_exit(0);
// }

int main(int argc, char *argv[])
{
	t_viewer v;
	v.names[0] = "Wolfgang junior";
	v.names[1] = "Mc Ron";
	v.names[2] = "Eude Herbert";
	v.names[3] = "Jacques-Henri";
	v.step = 40;

	pthread_t th_core, th_show;
	void *ret;

	rk_sema_init(&v.sem_ready2core, 0);
	rk_sema_init(&v.sem_ready2show, 0);

	if (pthread_create(&th_core, NULL, &core, &v) < 0) {
	  fprintf(stderr, "pthread_create error for th_core\n");
	  exit(1);
	}

	if (pthread_create(&th_show, NULL, &show, &v) < 0) {
	  fprintf(stderr, "pthread_create error for th_show\n");
	  exit(1);
	}

	(void)pthread_join(th_core, &ret);
	(void)pthread_join(th_show, &ret);

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
