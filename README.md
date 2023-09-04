# Philosophers

In this project, I learnt about multithreaded programs and concurrency. The exercise takes the famous Dining Philosopher problem from Dijkstra as a base case. We are asked to reproduce this problem and find its solution. To do so, I created n number of threads, each one representing a philosopher. The forks are represented by mutexes, therefore can only be accessed by one philosopher at a time.

To mitigate the risks of deadlocks, I initiate a sleep function after the creation of my threads; where philosophers' with even ID numbers would have to wait 50ms to start the execution. In regards to data races, I created various mutexes blocking off the access to variables shared by my "philosophers" and the main thread. In doing so, those variables could only be accessed by one philosopher or my main thread; this would eliminate the possibility of a read attempt and write attempt happening at the same time. Similarly to solving my program's data races, to protect my critical sections, I made use of mutexes to block off the accesses to other threads when in use.

## Installation

```bash
git clone git@github.com:PGCL1/Philosophers
cd Philosophers/philo
make
./philo philo-number time_to_die time_to_eat time_to_sleep [number_of_meals]
```
> [!NOTE]  
> All times passed as arguments should be in milliseconds, that way you won't have to wait ages to see the output :). In the example below, no one shoud die (see below): <br />
> ```bash
> ./philo 20 800 200 200 [5]
> ```

## Thank you

Thank you to the people that wrote these! Here's some ressources that really helped me doing this project:
* [Dining Philosopher Problem - Medium Article](https://medium.com/great-moments-in-computing-history/the-dining-philosophers-2e3da2847bac)
* [Threads & Concurrency](https://www.baeldung.com/cs/category/concurrency/tag/threads)
* [Scheduling Computing](https://en.wikipedia.org/wiki/Scheduling_(computing))

## My notes

All in all, this project for me, was a great learning path into concurrent programming, its advantages and drawbacks. It was also a stepping stone into understand deterministic programming and non-deterministic programming. I enjoyed my times with threads and hope to see more in the future. Peace!

G
