#include "philo.h"

int	error_manage(int error)
{
	if (error == 1)
		write (2, "Error: invalid args\n", 20);
	else if (error == 2)
		write (2, "Error when mutexing\n", 20);
	return (1);
}

void	destroy_data(t_data *data)
{
	int i;

	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->action_lock);
	pthread_mutex_destroy(&data->print_lock);
	free(data->philo);
	free(data->fork);
}
