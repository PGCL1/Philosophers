							Philo

TO-DO:


Improvements:



Learnings:
- errno 134 is triggered when memory usage becomes limited or unavailable (i.e occured when i tried to create 50 threads in my program)
- to prevent starvation from threads, we need to look into a method that is called ageing: where the OS looks for threads that have gone unrun for a long time and assigns those a higher priority -> which lets them jump the queue and get dealt with before competing threads

Philosophers' problems:
1. Deadlocks
2. Starvation
3. Race Conditions



