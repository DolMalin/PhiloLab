# Thread cheatsheet

```c
#include <pthread.h>
```

# pthread_create
Creates a new thread
## Synopsis
```c

int pthread_create(pthread_t * thread, pthread_attr_t * attr, void * (*start_routine)(void *), void * arg);
```
**thread = pointer to the thread

attr = attribute of the thread but can be Null because its attributed automaticaly

start_routine = function to call

arg = argument of the function in the start_routine funciton**

## Description
Creates a new thread executing simultaneously with the thread calling (the main function is also a thread). 

The new thread executes the function *start_routine* with *arg* as an argument.

The thread ends when the *start_routine* function ends or implicitely calling *pthread_exit*.
Both cases are equivalent to call pthread_exit with the return value of start_routine as the exit code.

The argument *attr* indicates the attributes of the new thread >> Meaning ?? see pthread_attr_init. 
*attr* can be NULL. In that case, default attributes are set, the thread is reachable (not detached) and is ordannanced normally (not in real time).

## Return value

Success : 0 + the ID of the new thread is stocked in the *thread* pointer.

Failure : non-null error code returned.

## Errors
EAGAIN : not enough system ressource to create a new thread or PTHREAD_THREAD_MAX reached

# pthread_detach
Puts an executing thread in detached state
```c
int pthread_detach(pthread_t th);
```
Puts the thread in the detached state. Frees the memory used for the *th* thread immediatly after the execution of *th*. But the other threads won't be able to know the death of *th* using *pthread_join*.

A thread can be created with the detachedmode with *pthread_create + detachstate* in attributes. Pthread_detach is usable only with threads created that are joinable. Must be put in detached state after.

## Return value
Success : 0
Failure : Non-nul return

## Errors
ESRCH : no thread found with the *th* number.
EINVAL : the th thread is already in detached state.


# pthread_join
Waits the end of another thread
## Synopsis
```c
int pthread_join(pthread_t th, void **thread_return);  
```
## Description
Can be used to join all the threads and avoid leaks.
Suspends the execution of the calling thread till the *th* thread is identified and finished its execution or if *pthread_exit* is called or the thread had been canceled.

If *thread_return* is not null, the *th* return value will be stocked there.

The *th* thread must be joinable.

When *th* is executed, the memory is not freed right away, it waits that all the pthreads_join used are executed.

## Return value
Success : 0 + return code of *th* stocked in *thread_return* 
Fail : non-null code return 


