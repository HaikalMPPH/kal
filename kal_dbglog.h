#pragma once

// Only works on debug mode
#ifdef DEBUG

#include "kal_defines.h"
#include <stdio.h>

#define kal_dbglog_err(format, ...)\
do {\
    fprintf(stderr, "[ERRO][%s:%s:%d]: ", __FILE__, __func__, __LINE__);\
    fprintf(stderr, format, __VA_ARGS__);\
} while (0)

#define kal_dbglog(format, ...)\
do {\
    fprintf(stdout, "[INFO][%s:%s:%d]: ", __FILE__, __func__, __LINE__);\
    fprintf(stdout, format, __VA_ARGS__);\
} while (0)

#else

#define kal_dbglog_err(format, ...)
#define kal_dbglog(format, ...)

#endif // DEBUG

