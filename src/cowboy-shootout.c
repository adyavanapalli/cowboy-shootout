// cowboy-shootout.c

#include <assert.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>

bool commence_shootout(size_t n_cowboys)
{
    while (n_cowboys > 1)
    {
        uint8_t* cowboys = calloc(n_cowboys, sizeof(uint8_t));
        assert(cowboys != NULL);

        size_t n_cowboys_killed = 0;
        for (size_t i = 0; i < n_cowboys; i++)
        {
            size_t offset_from_current_cowboy = 1 + (random() % (n_cowboys - 1));
            size_t index_of_target_cowboy = (i + offset_from_current_cowboy) % n_cowboys;

            if (cowboys[index_of_target_cowboy] == 0)
            {
                cowboys[index_of_target_cowboy] = 1;
                n_cowboys_killed++;
            }

            if (n_cowboys_killed == n_cowboys)
            {
                break;
            }
        }

        n_cowboys -= n_cowboys_killed;
        free(cowboys);
    }

    return n_cowboys == 1;

}

typedef struct iterate_params_t
{
    size_t n_cowboys;
    size_t n_trials;
} iterate_params_t;

void* iterate_shootouts(void* iterate_params)
{
    size_t n_cowboys = ((iterate_params_t*)iterate_params)->n_cowboys;
    size_t n_trials = ((iterate_params_t*)iterate_params)->n_trials;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <n_cowboys> <n_trials>\n", argv[0]);
        exit(-1);
    }

    size_t n_cowboys = strtoul(argv[1], NULL, 10);
    size_t n_trials = strtoul(argv[2], NULL, 10);

    size_t n_threads = (size_t)get_nprocs();

    pthread_t tid[n_threads];
    memset(tid, 0, n_threads * sizeof(pthread_t));

    iterate_params_t ip = { .n_cowboys = n_cowboys, .n_trials = n_trials / n_threads };

    for (size_t i = 0; i < n_threads; i++)
    {
        pthread_create(&tid[i], NULL, iterate_shootouts, &ip);
    }

    size_t n_trials_where_one_cowboy_survives = 0;
    for (size_t i = 0; i < n_trials; i++)
    {
        n_trials_where_one_cowboy_survives += commence_shootout(n_cowboys);
    }

    for (size_t i = 0; i < n_threads; i++)
    {
        pthread_join(tid[i], NULL);
    }

    double probability_of_one_cowboy_surviving = 1.0 * n_trials_where_one_cowboy_survives / n_trials;

    printf("For %lu cowboys, we have a %3.5f probability of one cowboy surviving [n_trials: %lu]\n",
           n_cowboys,
           probability_of_one_cowboy_surviving,
           n_trials);

    return 0;
}
