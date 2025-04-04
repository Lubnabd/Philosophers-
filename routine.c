#include "philo.h"
#include <unistd.h>

void	think(t_philo *philo)
{
	print_status("philosopher %d is thinking", philo);
	usleep(1000);
}

void	eat(t_philo *philo)
{
	if (philo->data->dead_flag)
		return ;

		pthread_mutex_lock(philo->first_fork);
		pthread_mutex_lock(philo->second_fork);

		print_status("is eating\n", philo);
		philo->last_meal_time = get_current_time();
		usleep(philo->data->time_to_eat * 1000);
		philo->meals_eaten++;

		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);

}

void	sleep_philo(t_philo *philo)
{
	print_status("Philosopher %d is sleeping...\n", philo);
	usleep(philo->data->time_to_sleep * 1000);
}

void	*routine(void *arg)
{
	(void)arg;
	/*t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep (1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->action_lock);
        if (philo->data->dead_flag)
        {
            pthread_mutex_unlock(&philo->data->action_lock);
            break;
        }
        pthread_mutex_unlock(&philo->data->action_lock);
		
		think(philo);
		eat(philo);
		sleep_philo(philo);
	}*/
usleep(1000);
printf("working\n");
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
			pthread_mutex_lock(&data->print_lock);
			printf("Failed to join thread for philosopher %d\n", i + 1);
			pthread_mutex_unlock(&data->print_lock);
			return (1);
		}
		i++;
	}
	return (0);
}
