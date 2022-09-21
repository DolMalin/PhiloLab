# Gettimeofday cheat sheet
Gets time of the day
```c
# include <sys/time.h>
```
## Synopsis
```c
int gettimeofday(struct timeval *tv, struct timezone *tz);
```

## Description
The following struct is in the sys/time.h library
```c
struct timeval
{
    time_t      tv_sec;  /* secondes */
    suseconds_t tv_usec; /* microsecondes */
};
```
The gettimeofday function gives the seconds and microseconds since the 1st January 1970.
It takes as a first argument a pointer to the struct below. 
The second argument tz(timezone) is often NULL.
FI : 1 second = 1 000 000 microseconds
