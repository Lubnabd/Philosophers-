#include "philo.h"

int	main(int argc, char **argv)
{
	(void)argv;
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("invalid args\n");
		return (1);
	}
	else
	{
		if (parse_args(&data, argc, argv))
			return (1);
	}
	pthread_mutex_init(&data.print_lock, NULL);
	data.dead_flag = 0;
	fork_init(&data);
	data.philo = philo_init(&data);
	if (!data.philo)
	{
		printf("Error: Philosopher initialization failed\n");
		return (1);
	}
	create_threads(&data);
	join_threads(&data);
	pthread_create(&data.monitor_thread, NULL, monitor, data.philo);
	free(data.philo);
	free(data.forks);
}
