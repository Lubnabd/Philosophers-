#include "philo.h"

void	*monitor(void *args)
{
	t_data	*data;
	int		i;
	int		all_ate;
	long	time_since_last_meal;

	data = (t_data *)args;
	while (1)
	{
		i = 0;
		all_ate = 1;
		while (i < data->philo_nbr)
		{
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
				return (NULL);
			}
			if (data->philo_meals_nbr != -1
				&& data->philo[i].meals_eaten < data->philo_meals_nbr)
				all_ate = 0;
			i++;
		}
		if (all_ate)
		{
			pthread_mutex_lock(&data->dead_flag_mutex);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->dead_flag_mutex);
			return (NULL);
		}
		usleep(1000);
	}
}
