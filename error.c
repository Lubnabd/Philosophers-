#include "philo.h"

int	error_manage(int error)
{
	if (error == 1)
		write (2, "Error: invalid args\n", 20);
	else if (error == 2)
		write (2, "Error when mutexing\n", 20);
	return 1;
}

/*void	mutex_handle()
{

}
void handle_mutex_error(){

} // same goes to threads for these two functions 

mutex_destroy ;*/