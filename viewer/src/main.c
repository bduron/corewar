#include "viewer.h"
#include <ncurses.h>

void	reamove(void *p, size_t size)
{
	printf("%s\n", (char *)p);
	(void)size;
	free(p);
}

int event_cmp(void *content, void *content_ref)
{
	ft_strcmp((char *)content, (char *)content_ref);
	return (0);
}

void *read_tab_process(void *arg)
{
	t_list	**events;

	events = (t_list **)arg;
	while (1)
	{
		printf("...\n");
		ft_lstremif(events, "NIMP", &event_cmp, &reamove);
		usleep(768);
	}
	pthread_exit (0);
}

void *write_tab_process(void *arg)
{
	t_list	**events;

	events = (t_list **)arg;
	while (1)
	{
		ft_lstpushback(events, "FORK", sizeof(char *));
		ft_lstpushback(events, "JUMP", sizeof(char *));
		usleep(497);
	}
	pthread_exit (0);
}

int main(void)
{
	t_list *events;
	pthread_t th1, th2;
	void *ret;

	events = NULL;

	// initscr();			/* Start curses mode 		*/
	// raw();				/* Line buffering disabled	*/
	// keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	// noecho();

	if (pthread_create(&th1, NULL, write_tab_process, &events) < 0)
	{
		fprintf(stderr, "pthread_create error for thread 1\n");
		exit(1);
	}

	if (pthread_create(&th2, NULL, read_tab_process, &events) < 0)
	{
		fprintf(stderr, "pthread_create error for thread 2\n");
		exit(1);
	}

	(void)pthread_join (th1, &ret);
	(void)pthread_join (th2, &ret);


	// endwin();
	return (0);
}
