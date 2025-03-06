#include "philo.h"

int	parse_args(t_data *data, int argc, char **argv) ////extracts user input and stores it in the t_data struct
{
	data->number_of_philosophers = atoi(argv[1]);
    data->time_to_die = atoi(argv[2]);
    data->time_to_eat = atoi(argv[3]);
    data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
        data->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
    else
        data->number_of_times_each_philosopher_must_eat = -1;
	if (data->number_of_philosophers <= 0 || data->time_to_die <= 0 || 
        data->time_to_eat <= 0 || data->time_to_sleep <= 0 || 
        (argc == 6 && data->number_of_times_each_philosopher_must_eat < 0))
		{
			printf("invalid args\n");
			return 1;
		}
    return (0);
}

void *routine(void *arg)
{
    (void)arg;
    printf("Philosopher started!\n");
    return NULL;
}

t_philo *init_philo(t_data *data);

int	main(int argc, char **argv)
{
	(void)argv;
	t_data data;
	t_philo *philos;
	int i;

	if (argc < 5 || argc > 6)
	{
		printf("invalid args\n");
		return (1);
	}
	parse_args(&data, argc, argv); //Calls parse_args to store arguments in t_data.

	philos = init_philo(&data);
    if (!philos)
        return (printf("Memory allocation failed\n"), 1);
	
	i = 0;
	while (i < data.number_of_philosophers) // use . instead of -> when accessing members of a normal struct.
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	printf("number_of_philosophers: %d, time_to_die: %d, time_to_eat: %d, time_to_sleep: %d, number_of_times_each_philosopher_must_eat: %d\n",
		data.number_of_philosophers, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.number_of_times_each_philosopher_must_eat);
	return (0);
}