#ifndef __EXCEPTION__
#define __EXCEPTION__

#include <iostream>

namespace Exception {

    class OUTOFBOUND: public std::exception{
        public:
        const char* what() const throw() {
            return "Out of Bounds!";
        }
    };

    class DIMENSIONMISMATCH: public std::exception{
        public:
        const char* what() const throw() {
            return "Dimension Mismatch!";
        }
    };

    class DIVIDEBYZERO: public std::exception{
        public:
        const char* what() const throw() {
            return "Divide by Zero!";
        }
    };

    class INITFAILED : public std::exception {
        public:
        const char* what() const throw() {
            return "Initialization Failed!";
        }
    };

    class PLOTFAILED : public std::exception {
        public:
        const char* what() const throw() {
            return "Error during plot!";
        }
    };
};

#endif