#ifndef _TIME_H_
#define _TIME_H_

#include <sys/time.h>

class Time {
    private:
        timeval start,end;
        bool isRunning;

    public:
        // Constructor
        Time();

        // Start the benchmark
        inline void start();

        // Stop the benchmark
        inline void stop();

        // Return the difference between start time
        // and stop time in micro seconds
        inline uintmax_t time();
};


inline Time::Time() : isRunning(false) {
}

// Start the benchmark
inline void Time::start() {
    if(!isRunning) {
        gettimeofday(&start,0);
        isRunning = true;
    }
}

// Stop the benchmark
inline void Time::stop() {
    if(isRunning){
        gettimeofday(&end,0);
        isRunning = false;
    }
}

// Return the difference between start time
// and stop time in micro seconds
inline uintmax_t Time::time() {
    return (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec);
}

#endif
