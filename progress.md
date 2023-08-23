							Philo

TO-DO:


Improvements:



Learnings:
- errno 134 is triggered when memory usage becomes limited or unavailable (i.e occured when i tried to create 50 threads in my program)
- to prevent starvation from threads, we need to look into a method that is called ageing: where the OS looks for threads that have gone unrun for a long time and assigns those a higher priority -> which lets them jump the queue and get dealt with before competing threads
- memset only works with 0 or -1 as it initializes only the first byte of the value (for example in an int there are 4 bytes, so memset would only initialize the first bytes with the given value). The only time it's ever really acceptable to write over a "blob" of data with non-byte datatype(s), is memset(thing, 0, sizeof(thing)); to "zero-out" the whole struture/array. This works because NULL, 0x00000000, 0.0, are all completely zeros.

Changes:
input my atoi function as atoi is not authorized
input time of death as a variable so 

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