# Mutex cheatsheet
A mutex (MUTual EXclusion) protects shared data of duplicated modifications.
Can be in 2 states : locked (taken by another thread) and unlocked (taken by no thread).
```c
#include <pthread.h>
```

## pthread_mutex_init
## Synopsis
```c
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);
```

## Description
initialize the mutex pointed by *mutex*.
If *mutexxattr* is NULL, default parameters are used.

## pthread_mutex_destroy
Destroys a mutex
```c
int pthread_mutex_destroy(pthread_mutex_t *mutex);  
```
Destroys a mutex if it's unlocked.
## pthread_mutex_lock
Locks a mutex
```c
int pthread_mutex_lock(pthread_mutex_t *mutex);
```
Locks the mutex. If the mutex is unlocked, it now belong to the thread calling pthread_mutex_lock. If the mutex is locked, the pthread_mutex_lock suspends the thread calling until the mutex is unlocked.

## pthread_mutex_unlock
Unlocks the mutex
```c
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```