# 🧠 Philosophers

## 📌 Table of Contents
- [Introduction](#introduction)
- [Project Objectives](#project-objectives)
- [Rules of the Simulation](#rules-of-the-simulation)
- [Compilation](#compilation)
- [Execution](#execution)
- [Parameters](#parameters)
- [Implementation Overview](#implementation-overview)
- [Resources](#resources)

---

## 🧩 Introduction

The **Philosophers** project is one of the foundational concurrency exercises at 42. It is based on the classic **Dining Philosophers Problem**, a synchronization problem that illustrates the challenges of avoiding deadlock and ensuring proper resource sharing among threads.

---

## 🎯 Project Objectives

- Understand the basics of **threads** in C using the `pthread` library.
- Learn how to properly use **mutexes** to protect shared resources.
- Ensure that the simulation behaves predictably and accurately under concurrent conditions.
- Prevent **deadlocks**, **race conditions**, and **starvation**.

---

## 🍝 Rules of the Simulation

- Philosophers sit at a round table.
- Each philosopher has a fork to their left and right (shared with neighbors).
- A philosopher must hold **both forks** to eat.
- After eating, the philosopher puts down the forks and starts **sleeping**, then **thinking**.
- If a philosopher does not eat within `time_to_die`, they **die** and the simulation ends.
- If the `number_of_times_each_philosopher_must_eat` is provided, the simulation ends when each philosopher has eaten at least that number of times.

---

## 🛠 Compilation

To compile the project, run:

```bash
make
````

This will generate the `philo` executable.

To clean up the object files (intermediate `.o` files), use:

```bash
make clean
```

To remove all compiled files including the executable:

```bash
make fclean
```

To clean and recompile everything from scratch:

```bash
make re
```

Ensure you are in the root directory of the project (where the `Makefile` is located) when running these commands.

---

## 🚀 Execution

Run the program using the following syntax:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

---

## 📥 Parameters

* `number_of_philosophers`: The number of philosophers (and forks).
* `time_to_die` (in milliseconds): Time a philosopher can live without eating.
* `time_to_eat` (in milliseconds): Time a philosopher spends eating.
* `time_to_sleep` (in milliseconds): Time a philosopher spends sleeping.
* `number_of_times_each_philosopher_must_eat` (optional): If all philosophers eat at least this many times, the simulation ends.

### Example:

```bash
./philo 5 800 200 200
```

This runs the simulation with 5 philosophers, each dying if they don't eat for 800ms, eating for 200ms, and sleeping for 200ms.

---

## 🧠 Implementation Overview

* Each philosopher is implemented as a **thread**.
* **Forks** are represented using **mutexes** to prevent concurrent access.
* Each philosopher tries to pick up the left and right fork (mutex lock).
* A global **monitor** thread checks for philosopher death and meal completion.
* **Logging** is synchronized to prevent interleaved output.
* Accurate **timing** is handled using `gettimeofday()` or a similar function.

---

## 📚 Resources

* [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
* man pages: `pthread_create`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_lock`, `usleep`, `gettimeofday`

---
🛠 Developed as part of the 42 Network's core curriculum
