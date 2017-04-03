#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#ifdef __APPLE__
	#include <dispatch/dispatch.h>
#else
	#include <semaphore.h>
#endif

struct rk_sema {
	#ifdef __APPLE__
		dispatch_semaphore_t    sem;
	#else
		sem_t                   sem;
	#endif
};

static inline void rk_sema_init(struct rk_sema *s, uint32_t value)
{
	#ifdef __APPLE__
		dispatch_semaphore_t *sem = &s->sem;
		*sem = dispatch_semaphore_create(value);
	#else
		sem_init(&s->sem, 0, value);
	#endif
}

static inline void rk_sema_wait(struct rk_sema *s)
{
	#ifdef __APPLE__
		dispatch_semaphore_wait(s->sem, DISPATCH_TIME_FOREVER);
	#else
		int r;
		do {
	sele		r = sem_wait(&s->sem);
		} while (r == -1 && errno == EINTR);
	#endif
}

static inline void rk_sema_post(struct rk_sema *s)
{
	#ifdef __APPLE__
		dispatch_semaphore_signal(s->sem);
	#else
		sem_post(&s->sem);
	#endif
}

// static sem_t my_sem;
static struct rk_sema my_sem;
int the_end;

void *thread1_process (void * arg)
{
  while (!the_end) {
    printf ("Je t'attend !\n");
    rk_sema_wait (&my_sem);
  }

  printf ("OK, je sors !\n");
  pthread_exit (0);
}

void *thread2_process (void * arg)
{
  register int i;

  for (i = 0 ; i < 5 ; i++) {
    printf ("J'arrive %d !\n", i);
    rk_sema_post (&my_sem);
    sleep (1);
  }

  the_end = 1;
  rk_sema_post (&my_sem); /* Pour debloquer le dernier sem_wait */
  pthread_exit (0);
}

main (int ac, char **av)
{
  pthread_t th1, th2;
  void *ret;

  // sem_init (&my_sem, 0, 0);
  rk_sema_init(&my_sem, 0);

  if (pthread_create (&th1, NULL, thread1_process, NULL) < 0) {
    fprintf (stderr, "pthread_create error for thread 1\n");
    exit (1);
  }

  if (pthread_create (&th2, NULL, thread2_process, NULL) < 0) {
    fprintf (stderr, "pthread_create error for thread 2\n");
    exit (1);
  }

  (void)pthread_join (th1, &ret);
  (void)pthread_join (th2, &ret);
}
