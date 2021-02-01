# Philosopher Problem

### Rule

- Philosophers sit around table.
- Philosophers do one thing among eating, sleeping, thinking.
- While doing one, can't do any else.
- Philosophers have to get two fork for each hands when eating.
- Philosophers sleep after eating, think after sleeping.
- Philosophers die when can't eating by long time.
- Philosophers always want to eat while thinking.

## philo_one

Argument : #of_phiosophers, time_to_die, time_to_eat, time_to_sleep, \[#of_times_each_philosopher_must_eat\]

1. Forks are setted at left & right sides of each philosophers.

2. Use pthread only, no semaphore.

## philo_two

Argument : #of_philosophers, time_to_die, time_to_eat, time_to_sleep, \[#of_times_each_philosopher_must_eat\]

1. Forks are setted on middle of table.

2. Use semaphore

## philo_three

Argument : number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, \[number_of_times_each_philosopher_must_eat\]

1. Forks are setted on middle of table.

2. Philosophers made by process(`fork()`).