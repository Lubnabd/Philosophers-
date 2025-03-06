#include "philo.h"

int	parse_args(t_data *data, int argc, char **argv) //extracts user input and stores it in the t_data struct
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

t_philo *init_philos(t_data *data)
{
	t_philo *philos;
    int i;

    philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
    if (!philos)
        return NULL;
    
    data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    if (!data->forks)
    {
        free(philos);
        return NULL;
    }

	i = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i + 1;
        philos[i].data = data;
        pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return philos;

}

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
	parse_args(&data, argc, argv);
	philos = init_philos(&data);
    if (!philos)
	{
		printf("Memory allocation failed\n");
		return 1;
	}

	// Create threads for each philosopher
for (i = 0; i < data.number_of_philosophers; i++)
{
    if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
    {
        printf("Error: Failed to create thread for philosopher %d\n", i + 1);
        return 1;
    }
}

for (i = 0; i < data.number_of_philosophers; i++)
    {
        pthread_join(philos[i].thread, NULL);
    }

	printf("number_of_philosophers: %d, time_to_die: %d, time_to_eat: %d, time_to_sleep: %d, number_of_times_each_philosopher_must_eat: %d\n",
		data.number_of_philosophers, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.number_of_times_each_philosopher_must_eat);

		free(philos);
    free(data.forks);
}

