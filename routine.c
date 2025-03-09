#include "philo.h"
#include <unistd.h>

void	think (t_philo *philo)
{
	printf("philosopher %d is thinking", philo->id);
	usleep(400);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id]);  // Lock left fork
    pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % philo->data->number_of_philosophers]); // Lock right fork

    printf("Philosopher %d is eating...\n", philo->id);
    usleep(philo->data->time_to_eat * 1000); // Simulate eating

    pthread_mutex_unlock(&philo->data->forks[philo->id]);  // Unlock left fork
    pthread_mutex_unlock(&philo->data->forks[(philo->id + 1) % philo->data->number_of_philosophers]); // Unlock right fork
}

void	sleep_philo(t_philo *philo)
{
	printf("Philosopher %d is sleeping...\n", philo->id);
    usleep(philo->data->time_to_sleep * 1000);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg; //Cast void pointer to t_philo *

    while (1)
    {
        think(philo);
        eat(philo);
        sleep_philo(philo);
    }

    return NULL;
}