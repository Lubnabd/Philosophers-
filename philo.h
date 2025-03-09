#ifndef PHILO_H
#define PHILO_H

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
	pthread_mutex_t		*forks;
} t_data;

typedef struct s_philo
{
    int             id;             // Philosopher ID
    pthread_t       thread;         // Thread representing the philosopher
    t_data          *data;          // Shared simulation data
} t_philo;

// we can do a struct for the forks and one for the philos // and a typedef struct for the table 

//int parse_args(t_data *data, int argc, char **argv);
//t_philo *init_philo(t_data *data); // Declare function here
void *routine(void *arg);
#endif