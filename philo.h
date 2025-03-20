//check you header again // struct for the fork & one for the philo & one for the program ?
#ifndef PHILO_H
#define PHILO_H

# define PHILO_MAX 	200
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <stdbool.h>
# include <sys/time.h>

typedef struct s_philo t_philo;

typedef	struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}	t_fork;

typedef struct s_data
{ //// our container of all data , here were gonna put all the inputs recieved in the command line 
	int					philo_nbr;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					philo_meals_nbr;
	int					dead_flag; // Stops simulation when set to 1
	long long			start_simulation;
	long long 			stop_simulation;
	pthread_mutex_t 	meal_time_mutex;
	pthread_mutex_t 	dead_flag_mutex; //Ensures safe access to dead_flag (since multiple threads read/write to it)
	pthread_mutex_t 	print_lock; // Mutex to prevent mixed-up print statements
	t_fork				*forks; //forks array 
	t_philo				*philo; //philos array
	pthread_t			monitor_thread;
} t_data;

typedef struct s_philo
{
    int             id;
	int				meals_eaten;
	long long		last_meal_time; //gettimeofday
    pthread_t       thread;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	bool			full; //a flag to check if a philosopher is full to stop them from eating
	t_data          *data;
} t_philo;

int 	parse_args(t_data *data, int argc, char **argv);
int		ft_atoi(const char *str);
void	fork_init(t_data *data);
t_philo	*philo_init(t_data *data);
void	init_program(t_data * data);
void 	*safe_malloc(size_t bytes);
int		error_manage(int error);
void 	create_threads(t_data *data);
void join_threads(t_data *data);
size_t	get_current_time();
void	*monitor(void *args);
void print_status(char *status, t_philo *philo);




#endif