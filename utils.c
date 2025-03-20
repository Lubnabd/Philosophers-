#include "philo.h"

int			ft_atoi(const char *str)
{
	int			sign;
	long		res;

	sign = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

void *safe_malloc(size_t bytes)
{
    void *ptr;

    ptr = malloc(bytes);
    if (!ptr)
	{
		//error_manage("error in the malloc\n");
		return (NULL);
	}
    return (ptr);
}

size_t		get_current_time()
{
	/*struct timeval
	{
		time_t		tv_sec; //seconds since jan 1 1970
		suseconds_t tv_usec; //10000000 micro = 1 sec
	}*/

	struct timeval current;
	gettimeofday(&current, NULL); // NULL because we don’t need timezone info
	return (current.tv_sec * 1000LL + current.tv_usec / 1000);
}
void print_status(char *status, t_philo *philo)
{
    pthread_mutex_lock(&philo->data->print_lock);
    printf("%ld %d %s\n", get_current_time(), philo->id, status);
    pthread_mutex_unlock(&philo->data->print_lock);
}