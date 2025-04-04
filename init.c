#include "philo.h"

int	fork_init(t_data *data)
{
	int	i;

	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo_nbr);
	if (!data->fork)
	{
		printf("memory allocation failed\n");
		return (1);
	}
	i = 0;
	while (i < data->philo_nbr)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->action_lock, NULL) != 0
		|| pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (1);
	return (0);
}

int	philo_init(t_data *data)
{
	int		i;

	i = 0;
	data->philo = malloc (sizeof(t_philo) * data->philo_nbr);
	if (!data->philo)
		return ;
	while (i < data->philo_nbr)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		data->philo[i].last_meal_time = get_current_time();
		data->philo[i].data = data;
		data->philo[i].first_fork = &data->fork[i];
		data->philo[i].second_fork = &data->fork[(i + 1)
			% data->philo_nbr];
		if (pthread_create(&data->philo[i].thread, NULL, &routine, &data->philo[i]) != 0)
			printf("creation failed\n");
		i++;
	}
	return (data->philo);
}

/*int	init_program(t_data *data)
{
	fork_init(data);
	philo_init(data);
	if (!data->philo)
		return (1);
	return (0);
}*/
