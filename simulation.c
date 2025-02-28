/* Manages philosophers' actions
Each philosopher runs in a thread and follows these steps:
Think
Take forks (mutex lock)
Eat
Put down forks (mutex unlock)
Sleep
Keep track of time and when each philosopher last ate.
*/
/*our goal is to simulate how philosophers behave when sitting around a table with forks:

Each philosopher thinks, eats, and sleeps.
Philosophers share forks, so they have to wait if a fork is not available.
If a philosopher does not eat within time_to_die, they die, and the simulation ends.
The simulation will use:

Threads (to run philosophers in parallel).
Mutexes (to prevent two philosophers from using the same fork at the same time).
At the end, our program will be like a real-life scenario, but inside a computer!

*/