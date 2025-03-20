/*A philosopher does not die by checking if they exceeded time_to_die without eating.
The simulation stops when all philosophers have eaten the required number of times.*/
/*The monitoring function must run in a separate thread to constantly check the state of philosophers while they continue eating, thinking, and sleeping.
This means you need one dedicated thread (pthread_create) for monitoring.*/

#include "philo.h"

//long get_time ()

void	*monitor(void *args)
{
	t_data *data;
	int i;
	int all_ate;

	data = (t_data *)args;
	while (1)
    {
        i = 0;
		all_ate = 1;
        while (i < data->philo_nbr)
        {
			// philosopher dies if too much time has passed since their last meal
            pthread_mutex_lock(&data->meal_time_mutex);
            long time_since_last_meal = get_current_time() - data->philo[i].last_meal_time;
            pthread_mutex_unlock(&data->meal_time_mutex);

			//If the Philosopher Has Starved
            if (time_since_last_meal >= data->time_to_die)
            {
				pthread_mutex_lock(&data->dead_flag_mutex);
                data->dead_flag = 1;
                pthread_mutex_unlock(&data->dead_flag_mutex);


                print_status("died", &data->philo[i]);
                //data->stop_simulation = 1;
                return NULL;
            }
			// Check if all philosophers ate enough
            if (data->philo_meals_nbr != -1 &&
                data->philo[i].meals_eaten < data->philo_meals_nbr)
                all_ate = 0;

            i++;
        }

		//If All Philosophers Have Eaten Enough, Stop the Simulation
        if (all_ate)
        {
            pthread_mutex_lock(&data->dead_flag_mutex);
            data->dead_flag = 1;
            pthread_mutex_unlock(&data->dead_flag_mutex);
            return NULL;
        }

        usleep(1000); // Prevents excessive CPU usage
    }
}



