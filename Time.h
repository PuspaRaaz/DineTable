#ifndef _TIME_H_
#define _TIME_H_

#include <sys/time.h>

class Time {
    private:
        timeval suru,antya;
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
        gettimeofday(&suru,0);
        isRunning = true;
    }
}

// Stop the benchmark
inline void Time::stop() {
    if(isRunning){
        gettimeofday(&antya,0);
        isRunning = false;
    }
}

// Return the difference between start time
// and stop time in micro seconds
inline uintmax_t Time::time() {
    return (antya.tv_sec * 1e6 + antya.tv_usec - suru.tv_sec * 1e6 - suru.tv_usec);
}

#endif
