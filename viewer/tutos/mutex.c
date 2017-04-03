#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static pthread_mutex_t my_mutex;

void *read_tab_process (void * arg)
{
  int i;

  pthread_mutex_lock (&my_mutex);
  for (i = 0 ; i != 5 ; i++)
    printf ("read_process, tab[%d] vaut %d\n", i, ((int *)arg)[i]);
  pthread_mutex_unlock (&my_mutex);
  pthread_exit (0);
}

void *write_tab_process (void * arg)
{
  int i;

  pthread_mutex_lock (&my_mutex);
  for (i = 0 ; i != 5 ; i++) {
    ((int *)arg)[i] = 2 * i;
    printf ("write_process, tab[%d] vaut %d\n", i, ((int *)arg)[i]);
    sleep (1); /* Relentit le thread d'ecriture... */
  }
  pthread_mutex_unlock (&my_mutex);
  pthread_exit (0);
}

main (int ac, char **av)
{
	int tab[5];
	pthread_t th1, th2;
	void *ret;

  pthread_mutex_init (&my_mutex, NULL);

  if (pthread_create (&th1, NULL, write_tab_process, &tab) < 0) {
    fprintf (stderr, "pthread_create error for thread 1\n");
    exit (1);
  }

  if (pthread_create (&th2, NULL, read_tab_process, &tab) < 0) {
    fprintf (stderr, "pthread_create error for thread 2\n");
    exit (1);
  }

  (void)pthread_join (th1, &ret);
  (void)pthread_join (th2, &ret);
}
