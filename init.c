#include "philo.h"

void	fork_init(t_data *data)
{
	int i;
	data->forks = safe_malloc(sizeof(t_fork) * data->philo_nbr);
	if (!data->forks)
	{
		printf("memory allocation failed\n");
		exit (1);
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		data->forks[i].fork_id = i;
		pthread_mutex_init(&data->forks[i].fork, NULL);
		i++;
	}
}

t_philo	*philo_init(t_data *data) //t_philo instead of void 
{
	t_philo	*philo;
	int i = 0;

	philo = safe_malloc(sizeof(t_philo) * data->philo_nbr);
	if (!philo)
		return (NULL);
	while ( i < data->philo_nbr)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		data->philo[i].last_meal_time = get_current_time(); //or 0??
		data->philo[i].data = data;
		data->philo[i].full = false;

		data->philo[i].first_fork = &data->forks[i].fork;
		data->philo[i].second_fork = &data->forks[(i + 1) % data->philo_nbr].fork;
		i++;
	}
	return (philo);
}

void	init_program(t_data * data)
{
	data->dead_flag = false;
	fork_init(data);
	data->philo = philo_init(data);
	if (!data->philo)
		exit(1);
}