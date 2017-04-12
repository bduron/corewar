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
	int stock;
	pthread_t thread_store;
	pthread_t thread_clients[NB_CLIENTS];
	pthread_mutex_t mutex_stock;
	pthread_cond_t cond_stock;
	pthread_cond_t cond_clients;
} store_t;

static store_t store = {
	.stock = INITIAL_STOCK,
	.mutex_stock = PTHREAD_MUTEX_INITIALIZER,
	.cond_stock = PTHREAD_COND_INITIALIZER,
	.cond_clients = PTHREAD_COND_INITIALIZER
};

static int get_random(int max)
{
	double val;

	val = (double) max * rand();
	val /= RAND_MAX + 1.0;
	return ((int)val);
}

static void *fn_store(void *p_data)
{
	while (1)
	{
		pthread_mutex_lock(&store.mutex_stock);
		pthread_cond_wait(&store.cond_stock, &store.mutex_stock);
		store.stock = INITIAL_STOCK;
		printf("Remplissage du stock de %d articles !\n", store.stock);
		pthread_cond_signal(&store.cond_clients);
		pthread_mutex_unlock(&store.mutex_stock);
	}
	return (NULL);
}

static void *fn_clients(void *p_data)
{
	int nb = *(int *)p_data;
	while (1)
	{
		int val = get_random(6);
		pthread_mutex_lock(&store.mutex_stock);
		psleep(get_random(3));
		if (val > store.stock)
		{
			pthread_cond_signal(&store.cond_stock);
			pthread_cond_wait(&store.cond_clients, &store.mutex_stock);
		}
		store.stock = store.stock - val;
		printf("Client %d prend %d du stock, reste %d en stock !\n", nb, val, store.stock);
		pthread_mutex_unlock(&store.mutex_stock);
	}
	return (NULL);
}

int main(void)
{
	int client_numbers[NB_CLIENTS];
	int ret = 0;

	printf("Creation du thread du magasin !\n");
	ret = pthread_create(&store.thread_store, NULL, &fn_store, NULL);
	/* Creation des threads des clients si celui du magasin a reussi. */
	if (! ret)
	{
		printf ("Creation des threads clients !\n");
		for (int i = 0; i < NB_CLIENTS; i++)
		{
			client_numbers[i] = i;
			ret = pthread_create(&store.thread_clients[i], NULL, fn_clients, &client_numbers[i]);
			if (ret)
			{
				fprintf (stderr, "%s", strerror (ret));
			}
		}
	}
	else
	{
		fprintf (stderr, "%s", strerror (ret));
	}
	/* Attente de la fin des threads. */
	for (int i = 0; i < NB_CLIENTS; i++)
	{
		pthread_join (store.thread_clients[i], NULL);
	}
	pthread_join (store.thread_store, NULL);
	return EXIT_SUCCESS;
}
