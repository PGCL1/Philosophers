							Philo

TO-DO:


Improvements:



Learnings:
- errno 134 is triggered when memory usage becomes limited or unavailable (i.e occured when i tried to create 50 threads in my program)
- to prevent starvation from threads, we need to look into a method that is called ageing: where the OS looks for threads that have gone unrun for a long time and assigns those a higher priority -> which lets them jump the queue and get dealt with before competing threads
- memset only works with 0 or -1 as it initializes only the first byte of the value (for example in an int there are 4 bytes, so memset would only initialize the first bytes with the given value). The only time it's ever really acceptable to write over a "blob" of data with non-byte datatype(s), is memset(thing, 0, sizeof(thing)); to "zero-out" the whole struture/array. This works because NULL, 0x00000000, 0.0, are all completely zeros.

Philosophers' problems:
1. Deadlocks
2. Starvation
3. Race Conditions


About the logs of your program:
	• Any state change of a philosopher must be formatted as follows:
		◦ timestamp_in_ms X has taken a fork
		◦ timestamp_in_ms X is eating
		◦ timestamp_in_ms X is sleeping
		◦ timestamp_in_ms X is thinking
		◦ timestamp_in_ms X died
	Replace timestamp_in_ms with the current timestamp in milliseconds
	and X with the philosopher number.
	• A displayed state message should not be mixed up with another message.
	• A message announcing a philosopher died should be displayed no more than 10 ms
	after the actual death of the philosopher.
	• Again, philosophers should avoid dying!

	The specific rules for the mandatory part are:
	• Each philosopher should be a thread.
	• There is one fork between each pair of philosophers. Therefore, if there are several
	philosophers, each philosopher has a fork on their left side and a fork on their right
	side. If there is only one philosopher, there should be only one fork on the table.
	• To prevent philosophers from duplicating forks, you should protect the forks state
	with a mutex for each of them.

	Authorized functions are:
	*	memset
	*	printf
	*	malloc
	*	free
	*	write
	*	usleep
	*	gettimeofday
	*	pthread_create
	*	pthread_detach
	*	pthread_join
	*	pthread_mutex_init
	*	pthread_mutex_destroy
	*	pthread_mutex_lock,
	*	pthread_mutex_unlock