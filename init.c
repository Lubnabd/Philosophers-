#include "philo.h"

int	fork_init(t_data *data)
{
	int	i;

	data->fork = safe_malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
	if (!data->fork)
	{
		printf("memory allocation failed\n");
		return (1);
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			retrun (1);
		i++;
	}
	if (pthread_mutex_init(&data->action_lock, NULL) != 0
		|| pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (1);
	return (0);
}

t_philo	*philo_init(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = safe_malloc (sizeof(t_philo) * data->philo_nbr);
	if (!philo)
		return (NULL);
	while (i < data->philo_nbr)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		data->philo[i].last_meal_time = get_current_time();
		data->philo[i].data = data;
		data->philo[i].first_fork = &data->fork[i];
		data->philo[i].second_fork = &data->fork[(i + 1)
			% data->philo_nbr];
		pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]);
		i++;
	}
	return (philo);
}

int	init_program(t_data *data)
{
	fork_init(data);
	data->philo = philo_init(data);
	if (!data->philo)
		return (1);
	return (0);
}
