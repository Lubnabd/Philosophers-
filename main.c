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
    return (0);
}

int	main(int argc, char **argv)
{
	(void)argv;
	t_data data;

	if (argc < 2)
	{
		printf("invalid args\n");
		return (1);
	}
	parse_args(&data, argc, argv); //Calls parse_args to store arguments in t_data.

	printf("number_of_philosophers: %d, time_to_die: %d, time_to_eat: %d, time_to_sleep: %d, number_of_times_each_philosopher_must_eat: %d\n",
		data.number_of_philosophers, data.time_to_die, data.time_to_eat, data.time_to_sleep, data.number_of_times_each_philosopher_must_eat);
	return (0);
}