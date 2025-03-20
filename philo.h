#ifndef PHILO_H
# define PHILO_H

# define PHILO_MAX 200

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

// Struct to store all input data and simulation parameters
typedef struct s_data
{
	int				philo_nbr;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_meals_nbr;
	int				dead_flag;
	long long		start_simulation;
	pthread_mutex_t	action_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*fork;
	t_philo			*philo;
	pthread_t		monitor_thread;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	t_data			*data;
}	t_philo;

int		parse_args(t_data *data, int argc, char **argv);
int		ft_atoi(const char *str);
void	fork_init(t_data *data);
t_philo	*philo_init(t_data *data);
void	init_program(t_data *data);
void	*routine(void *arg);
void	*safe_malloc(size_t bytes);
int		error_manage(int error);
void	create_threads(t_data *data);
void	join_threads(t_data *data);
size_t	get_current_time(void);
void	*monitor(void *args);
void	print_status(char *status, t_philo *philo);

#endif
