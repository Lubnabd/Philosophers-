#include "philo.h"

int	parse_args(t_data *data, int argc, char **argv)
{
	data->philo_nbr = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->philo_meals_nbr = ft_atoi(argv[5]);
	else
		data->philo_meals_nbr = -1;
	if (data->philo_nbr <= 0 || data->philo_nbr > PHILO_MAX
		|| data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || (argc == 6 && data->philo_meals_nbr < 0))
	{
		printf("invalid args\n");
		return (1);
	}
	return (0);
}
