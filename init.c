#include "philo.h"

t_philo *init_philo(t_data *data)
{
    t_philo *philos = malloc (sizeof(t_philo) * data->number_of_philosophers);
    if (!philos)
        return (NULL);
        int i = 0;
        while ( i < data->number_of_philosophers)
        {
            philos[i].id = i + 1;
            philos[i].data = data;
            pthread_mutex_init(&philos[i].left_fork, NULL);
            i++;
        }
        
        return (philos);
}