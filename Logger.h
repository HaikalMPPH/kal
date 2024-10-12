#ifndef LOGGER_H
#define LOGGER_H

// Only works on debug mode
#ifdef DEBUG
#include <stdio.h>
    // LOG_STR: String only logger.
    //  str: The string that will be logged.
    #define DEBUG_LOG_MSG(status, str)\
        DEBUG_LOG(status, "%s", str)

    // LOG: Default logger. Only works on debug build.
    //   format: stdio like string format.
    //   ...     : Logged arguments.
    #define DEBUG_LOG(status, format, ...)\
    do {\
        printf("["#status"][" __FILE__ "][%s]: ", __func__);\
        printf(format, __VA_ARGS__);\
        printf("\n");\
    } while (0)
#else
    #define DEBUG_LOG_MSG(...)
    #define DEBUG_LOG(...)
#endif // DEBUG

#endif // LOGGER_H

