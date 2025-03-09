////why would i use -lpthread in makefile? and do i have to mention it i the name rule? 
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

	// Initialize forks (mutexes)
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i + 1;
        philos[i].data = data;
        pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	// Initialize philosophers and assign forks
    for (i = 0; i < data->number_of_philosophers; i++)
    {
        philos[i].id = i + 1;
        philos[i].data = data;
        data[i].forks = &data->forks[i];                   // Left fork
        data[i].forks = &data->forks[(i + 1) % data->number_of_philosophers]; // Right fork (circular assignment) //The modulus (%) ensures the last philosopher (index N-1) gets the first fork (index 0), forming a circular dining table.
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
    { //If a thread fails to create, you should destroy mutexes and free memory before exiting.
        printf("Error: Failed to create thread for philosopher %d\n", i + 1);
// Free allocated resources before exiting
while (--i >= 0)
pthread_join(philos[i].thread, NULL);

		free(philos);
    free(data.forks);
	return 1;
	}
}
 // Wait for all threads to finish
 for (i = 0; i < data.number_of_philosophers; i++)
 pthread_join(philos[i].thread, NULL);

// Destroy mutexes
for (i = 0; i < data.number_of_philosophers; i++)
 pthread_mutex_destroy(&data.forks[i]);

free(philos);
free(data.forks);
}
/*./philo 100 800 200 200*/