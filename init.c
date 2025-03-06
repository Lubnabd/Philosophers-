#include "philo.h"

t_philo *init_philo(t_data *data)
{
    t_philo *philos;
    int i;

    philos = malloc (sizeof(t_philo) * data->number_of_philosophers);
    if (!philos)
        return (NULL);
    
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    if (!data->forks)
    {
        free(philos);
        return (NULL);
    }
    i = 0;
    while ( i < data->number_of_philosophers)
    {
        philos[i].id = i + 1;
        philos[i].data = data;
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
        
        return (philos);
}