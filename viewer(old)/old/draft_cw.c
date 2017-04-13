#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#define psleep(sec) sleep ((sec))
#define INITIAL_STOCK 20
#define NB_CLIENTS 5

typedef struct
{
	int i;

	pthread_t thread_compute;
	pthread_t thread_render;
	pthread_t thread_timer;

	pthread_mutex_t mutex_compute;
	pthread_mutex_t mutex_timer;

	pthread_cond_t cond_compute;
	pthread_cond_t cond_render;
	pthread_cond_t cond_timer;

} viewer_t;

static viewer_t viewer = {
	.i = 0,

	.mutex_compute = PTHREAD_MUTEX_INITIALIZER,
	.mutex_timer = PTHREAD_MUTEX_INITIALIZER,

	.cond_compute = PTHREAD_COND_INITIALIZER,
	.cond_render = PTHREAD_COND_INITIALIZER,
	.cond_timer = PTHREAD_COND_INITIALIZER
};

static void *fn_compute(void *p_data)
{
	while (1)
	{
		printf("C\n");
		pthread_mutex_lock(&viewer.mutex_compute);
		pthread_cond_wait(&viewer.cond_render, &viewer.mutex_compute);

		viewer.i++;

		pthread_cond_signal(&viewer.cond_compute);
		pthread_mutex_unlock(&viewer.mutex_compute);
	}
	return (NULL);
}

static void *fn_render(void *p_data)
{
	while (1)
	{
		printf("R\n");
		pthread_mutex_lock(&viewer.mutex_compute);
		pthread_mutex_lock(&viewer.mutex_timer);
		pthread_cond_wait(&viewer.cond_compute, &viewer.mutex_compute);
		pthread_cond_wait(&viewer.cond_timer, &viewer.mutex_timer);

		printf("rendering loop %d\n", viewer.i);

		pthread_cond_broadcast(&viewer.cond_render);
		pthread_mutex_unlock(&viewer.mutex_compute);
		pthread_mutex_unlock(&viewer.mutex_timer);
	}
	return (NULL);
}

static void *fn_timer(void *p_data)
{
	while (1)
	{
		printf("T\n");
		pthread_mutex_lock(&viewer.mutex_timer);
		pthread_cond_wait(&viewer.cond_render, &viewer.mutex_timer);

		sleep(1);

		pthread_cond_signal(&viewer.cond_timer);
		pthread_mutex_unlock(&viewer.mutex_timer);
	}
	return (NULL);
}

int main(void)
{
	pthread_create(&viewer.thread_compute, NULL, &fn_compute, NULL);
	pthread_create(&viewer.thread_render, NULL, &fn_render, NULL);
	pthread_create(&viewer.thread_timer, NULL, &fn_timer, NULL);

	// pthread_cond_broadcast(&viewer.cond_render);

	printf("COUCOU\n");

	pthread_join(viewer.thread_compute, NULL);
	pthread_join(viewer.thread_render, NULL);
	pthread_join(viewer.thread_timer, NULL);

	return EXIT_SUCCESS;
}
