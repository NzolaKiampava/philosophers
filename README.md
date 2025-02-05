
# 🧘 Philosophers 42 Project

<img src="https://img.shields.io/badge/Grade-100%2F100-success"></img>

The <b>Philosophers</b> project is a classic concurrent programming exercise from the 42 school curriculum. The aim of the project is to simulate a variation of the Dining Philosophers Problem, showcasing fundamental concepts in multithreading, process synchronization, and avoiding deadlocks.

In this simulation, multiple philosophers sit at a round table, alternating between eating, sleeping, and thinking. Each philosopher needs two forks to eat, but there are only as many forks as there are philosophers, leading to the need for synchronization and careful management of shared resources.

![It is an image](https://github.com/NzolaKiampava/philosophers/blob/main/image.png)

## Table of Contents
- [Overview](#overview)
- [Requirements](#requirements)
- [Compilation](#compilation)
- [Usage](#usage)
  - [Example](#example)
- [Explanation of Arguments](#explanation-of-arguments)
- [Additional Information](#additional-information)

---

## Overview

The <b>Dining Philosophers Problem</b> involves five <b>philosophers</b> seated at a round table with a fork between each pair. Philosophers alternate between thinking, eating, and sleeping:
- **Thinking**: The philosopher contemplates the mysteries of the universe.
- **Eating**: The philosopher picks up two forks, one on each side, and eats.
- **Sleeping**: The philosopher rests after eating.

The simulation ends when each philosopher has eaten a specified number of times or if a philosopher "dies" by not eating within a given time frame.

### Project Objectives
- Understand multithreading using POSIX threads (`pthread` library).
- Implement mutexes to protect shared resources.
- Avoid deadlocks and ensure safe resource sharing between threads.

---

## Requirements

- **Operating System**: Unix-based (Linux or macOS)
- **Compiler**: `gcc` or equivalent with C99 standard support.
- **Libraries**: `pthread` library for multithreading

---

## Compilation

To compile the project, navigate to the project directory and run:

```bash
make
```

This will produce an executable called `philo`.

---

## Usage

The `philosophers` program accepts the following command-line arguments:

```bash
./philo [num_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [num_meals]
```

- **num_philosophers**: Number of philosophers and forks.
- **time_to_die**: Time in milliseconds a philosopher can live without eating.
- **time_to_eat**: Time in milliseconds a philosopher needs to eat.
- **time_to_sleep**: Time in milliseconds a philosopher will sleep after eating.
- **num_meals** *(optional)*: Minimum number of times each philosopher must eat. The simulation ends when all philosophers have eaten this number of times. If not specified, the simulation only ends if a philosopher dies.

### Example

```bash
# Run the simulation with 5 philosophers, 800ms to live without eating,
# 200ms to eat, 200ms to sleep, and each philosopher must eat 7 times.
./philo 5 800 200 200 7
```

In this example:
- If a philosopher does not eat within 800ms, they "die," and the simulation ends.
- Each philosopher eats for 200ms, sleeps for 200ms, and the simulation completes when all philosophers have eaten at least 7 times.

---

## Explanation of Arguments

- **Philosopher Count**: Controls the number of threads. Ensure the number is greater than 1 to avoid deadlocks.
- **Time to Die**: If a philosopher's last meal time exceeds this time, they "die," ending the simulation. This demonstrates the need for each philosopher to access shared resources (forks) regularly.
- **Time to Eat/Sleep**: Controls philosopher activity cycles, illustrating synchronization between threads.
- **Number of Meals**: Defines how often each philosopher needs to eat before the simulation ends. Optional parameter to prevent infinite simulation.

---

## Additional Information

This project provides insight into concurrency issues and challenges in resource allocation. Some key elements include:

- **Avoiding Deadlock**: By managing the order of fork pickups and using mutexes to control access, the program aims to prevent deadlock situations.
- **Race Conditions**: By locking shared resources before access, the code prevents race conditions.
- **Termination Conditions**: The simulation stops either when a philosopher "dies" or when all philosophers meet the minimum meal requirement.

### Notes
- Tuning the parameters (e.g., time to eat/sleep) can result in different behaviors and highlight synchronization challenges.
- Philosophers are not allowed to "die" silently; a message will print when any philosopher fails to eat in the allotted time.

---

## Test Case Checks


```bash
./philo 1 800 200 200
#  Single philosopher should die,
#  Only one fork available, can't eat

./philo 4 310 200 100
#  Should die due to tight timing
#  Time to die (310ms) is less than time needed for two eating cycles

./philo 4 200 205 200
#  Should die due to timing
#  Time to eat (205ms) is greater than time to die (200ms)

./philo 5 800 200 200 7
#  No deaths, stops after 7 meals
#  Enough time between meals, stops when all philosophers eat 7 times

./philo 4 410 200 200 10
#  No deaths, stops after 10 meals
#  Sufficient timing for survival, stops after 10 meals

____________________________________________________________
# All negative number cases should be caught by input validation
#  Key validation checks:
    #No negative numbers Valid number of arguments Numbers within reasonable ranges All arguments are valid integers

```
---

## License

This project is part of the 42 curriculum and intended for educational purposes.
In case of doubts feel free to reach me on my email [nzolakiampava@gmail.com]! 
