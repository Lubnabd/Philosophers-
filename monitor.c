#include "philo.h"

void	check_death(t_data *data, int i)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&data->meal_time_mutex);
	time_since_last_meal = get_current_time()
		- data->philo[i].last_meal_time;
	pthread_mutex_unlock(&data->meal_time_mutex);
	if (time_since_last_meal >= data->time_to_die)
	{
		pthread_mutex_lock(&data->dead_flag_mutex);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->dead_flag_mutex);
		print_status("died", &data->philo[i]);
	}
}

int	check_all_ate(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_nbr)
	{
		if (data->philo_meals_nbr != -1
			&& data->philo[i].meals_eaten < data->philo_meals_nbr)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor(void *args)
{
	t_data	*data;
	int		i;

	data = (t_data *)args;
	while (1)
	{
		i = 0;
		while (i < data->philo_nbr)
		{
			check_death(data, i);
			i++;
		}
		if (check_all_ate(data))
		{
			pthread_mutex_lock(&data->dead_flag_mutex);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->dead_flag_mutex);
			return (NULL);
		}
		usleep(1000);
	}
}
