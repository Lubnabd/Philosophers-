/*You can’t have more than 10 ms between the death of a philosopher and when it
will print its death.*/
#include "philo.h"

int	main(int argc, char **argv)
{
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
	fork_init(&data);
	philo_init(&data);
	if (!data.philo)
	{
		printf("Error: Philosopher initialization failed\n");
		return (1);
	}
	join_threads(&data);
	
	//pthread_create(&data.monitor_thread, NULL, &monitor, &data.philo);
	//pthread_join(data.monitor_thread, NULL);
	destroy_data(&data);
}
