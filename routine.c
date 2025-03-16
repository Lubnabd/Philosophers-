#include "philo.h"
#include <unistd.h>

void	think (t_philo *philo)
{
	printf("philosopher %d is thinking", philo->id);
	usleep(1000);
}

void	eat(t_philo *philo)
{
	// Deadlock prevention: Odd philosophers pick up right fork first, then left
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&philo->data->forks[philo->id].fork); // Lock left fork
        pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % philo->data->philo_nbr].fork); // Lock right fork
    }
    else
    {
        pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % philo->data->philo_nbr].fork); // Lock right fork
        pthread_mutex_lock(&philo->data->forks[philo->id].fork); // Lock left fork
    }
    printf("Philosopher %d is eating...\n", philo->id);
    usleep(philo->data->time_to_eat * 1000); // Simulate eating

    pthread_mutex_unlock(&philo->data->forks[philo->id].fork);  // Unlock left fork
    pthread_mutex_unlock(&philo->data->forks[(philo->id + 1) % philo->data->philo_nbr].fork); // Unlock right fork
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

void create_threads(t_data *data)
{
    int i;

    // Creating a thread for each philosopher
    for (i = 0; i < data->philo_nbr; i++)
    {
        if (pthread_create(&data->philo[i].thread, NULL, routine, &data->philo[i]) != 0)
        {
            printf("Failed to create thread for philosopher %d\n", i + 1);
            exit(1);
        }
    }
}

// Function to join threads after they are done
void join_threads(t_data *data)
{
    int i;

    // Joining each philosopher's thread
    for (i = 0; i < data->philo_nbr; i++)
    {
        if (pthread_join(data->philo[i].thread, NULL) != 0)
        {
            printf("Failed to join thread for philosopher %d\n", i + 1);
            exit(1);
        }
    }
}

/* pthread_mutex_lock expects a pointer to a pthread_mutex_t type, but you're passing a pointer to a t_fork struct. The t_fork struct contains a pthread_mutex_t field, so you need to access that field in order to lock the mutex.*/