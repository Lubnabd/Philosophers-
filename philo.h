#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_data //to make it easier to declare variables of that type.

{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philosopher_must_eat;
} t_data;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	t_data		*data;
	pthread_mutex_t	left_fork;
} t_philo;