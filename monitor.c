#include "philo.h"

int	check_death(t_data *data, int i)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&data->action_lock);
	if (data->dead_flag == 1) {
        pthread_mutex_unlock(&data->action_lock);
        return (1);  // Exit early if someone has already died
    }
	time_since_last_meal = get_current_time() - data->philo[i].last_meal_time;
	pthread_mutex_unlock(&data->action_lock);
	if (time_since_last_meal >= data->time_to_die)
	{
		pthread_mutex_lock(&data->action_lock);
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->action_lock);
		print_status("died", &data->philo[i]);
		return (1);
	}
	return (0);
}

int	check_all_ate(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_lock(&data->action_lock);
		if (data->philo_meals_nbr != -1
			&& data->philo[i].meals_eaten < data->philo_meals_nbr)
			{
				pthread_mutex_unlock(&data->action_lock);
				return (0);
			}
		pthread_mutex_unlock(&data->action_lock);
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
			if (check_death(data, i))
                return (NULL);  // If someone died, stop the monitor thread
            i++;
		}
		pthread_mutex_lock(&data->action_lock);
		if (data->dead_flag == 1 || check_all_ate(data))
		{
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->action_lock);
			break;
		}
			pthread_mutex_unlock(&data->action_lock);
			usleep (1000);
		}
		return (NULL);
}

