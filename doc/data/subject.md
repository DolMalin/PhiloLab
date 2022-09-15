# Philosophers

![Philosophers](../assets/philo.png)

## Goal

	Resolve the philosopher's dinner problem and get a comprehension of threading, mutex and processes in C.

## Context
- Some **philosophers** will be sitting around a table, in which there is a plate of spaghetti in the middle.

- During this dinner, they have to **eat**, **think** or **sleep**.
- They can only do **one thing** at a time:
	- When they are eating, they can't think or sleep.
	- When they are sleeping, they can't eat or think
	- When they are think, they can't eat or sleep
- They are **as many forks** as philosophers on the table *(1 philosopher = 1 fork)*.
- Each philosopher needs **two forks to eat** *(eat = 2 forks)*.
- When a philosopher finish to eat, he **drops the forks** back on the table, and **starts sleeping**.
- Once a philosopher finish to sleep, he **starts to think**
- The simulation **stops** if a philosopher **dies starving**.
- Philsophers **don't communicate** with each others.
- The time_to_die must be **lower** than the time between the **start of his last meal** and the **start of his next meal**

## Rules
- **Global variables** are forbidden
- Each program must take the following arguments:
	- **number_of_philosophers** (also number of forks)
	- **time_to_die** (*in miliseconds*, if a philosopher didn't **start** to eat)
	- **time_to_eat** (*in miliseconds*, the time a philospher needs to **eat** and **keep his two forks**)
	- **time_to_sleep** (*in miliseconds*, the time a philosopher will have to **sleep**)
	- **number_of_times_each_philosopher_must_eat** (*optional* the number of meal that the philsophers will have **before the program stops**, if not specified, the dinner stops at the death of a philosopher)
- Each philosopher is **assigned** to a **unique number** between 1 and number_of_philosophers
- Each philosopher sits between number N - 1 and N + 1
- Each [state change/action] must be logged in the console as follows:
	- timestamp_in_ms X has taken a fork
	- timestamp_in_ms X is eating
	- timestamp_in_ms X is thinking
	- timestamp_in_ms X died

		*X refers to the philosopher number*
- **Any message can't be mixed** with another message
- The death of a philosopher can't be **announced later than 10ms**
- Philosophers must avoid to die
- Each philosopher must be represented by a **thread**
- Each fork is placed **beetween** each pair of philosophers. That means each philsophers has a fork on his right and his left. If there is only one philosopher, there will be one fork
- To avoid the philsopher to duplicate the forks, you must **protect the forks with a mutex** for each fork.

## Mandatory Part

| Program name |philo|
| :---- | :------- |
|Expected files |Makefile, *.h, *.c, in a philo/ folder |
| Makefile    | NAME, all, clean, fclean, re|
| Arguments   | number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]|
| Authorized functions    | memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock |
| Libft authorized    | no |
| Description  | Philosophers witch threads and mutex |
