////why would i use -lpthread in makefile? and do i have to mention it i the name rule? 
#include "philo.h"

int	main(int argc, char **argv)
{
	(void)argv;
	t_data data;
	//t_philo *philos;
	//int i;

	if (argc < 5 || argc > 6)
	{
		printf("invalid args\n");
		return (1);
	}
	else
	{
		if (parse_args(&data, argc, argv))
			return 1;
	}
	// Initialize mutexes and data
    pthread_mutex_init(&data.print_lock, NULL);
    data.dead_flag = 0;  // Initializing dead flag (no philosopher is dead initially)

    // Initialize forks and philosophers
    fork_init(&data);
    data.philo = philo_init(&data);
    if (!data.philo)
    {
        printf("Error: Philosopher initialization failed\n");
        return 1;
    }

    // Create threads for philosophers
    create_threads(&data);

    // Join threads after they finish
    join_threads(&data);

    // Cleanup resources
    free(data.philo);
    free(data.forks);
}





	/*philos = init_philos(&data);
    if (!philos)
	{
		printf("Memory allocation failed\n");
		return 1;
	}

	// Create threads for each philosopher
for (i = 0; i < data.philo_nbr; i++)
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
 for (i = 0; i < data.philo_nbr; i++)
 pthread_join(philos[i].thread, NULL);

// Destroy mutexes
for (i = 0; i < data.philo_nbr; i++)
 pthread_mutex_destroy(&data.forks[i]);

free(philos);
free(data.forks);
}*/
/*./philo 100 800 200 200*/