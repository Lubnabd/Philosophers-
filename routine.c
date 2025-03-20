#include "philo.h"
#include <unistd.h>

void	think(t_philo *philo)
{
	printf("philosopher %d is thinking", philo->id);
	usleep(1000);
}

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->id].fork);
		pthread_mutex_lock(&philo->data->forks[(philo->id + 1)
			% philo->data->philo_nbr].fork);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[(philo->id + 1)
			% philo->data->philo_nbr].fork);
		pthread_mutex_lock(&philo->data->forks[philo->id].fork);
	}
	printf("Philosopher %d is eating...\n", philo->id);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->id].fork);
	pthread_mutex_unlock(&philo->data->forks[(philo->id + 1)
		% philo->data->philo_nbr].fork);
}

void	sleep_philo(t_philo *philo)
{
	printf("Philosopher %d is sleeping...\n", philo->id);
	usleep(philo->data->time_to_sleep * 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		think(philo);
		eat(philo);
		sleep_philo(philo);
	}
	return (NULL);
}

int	join_threads(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
		{
			printf("Failed to join thread for philosopher %d\n", i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}
