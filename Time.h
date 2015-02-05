#ifndef _TIME_H_
#define _TIME_H_

#include <sys/time.h>

class Time {
    private:
        timeval m_start,m_end;
        bool m_running;

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


inline Time::Time() : m_running(false) {
}

// Start the benchmark
inline void Time::start() {
    if(!m_running) {
        gettimeofday(&m_start,0);
        m_running = true;
    }
}

// Stop the benchmark
inline void Time::stop() {
    if(m_running){
        gettimeofday(&m_end,0);
        m_running = false;
    }
}

// Return the difference between start time
// and stop time in micro seconds
inline uintmax_t Time::time() {
    if(m_running){
        std::cout<<"WTF!!!\n";
        throw "WTF!!!";
    }
    return (m_end.tv_sec * 1e6 + m_end.tv_usec - m_start.tv_sec * 1e6 - m_start.tv_usec);
}

#endif
