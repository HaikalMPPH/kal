#pragma once

// Only works on debug mode
#ifdef DEBUG

#include "kal_defines.h"
#include <stdio.h>

#define kal_dbglog_err(...)\
do {\
    fprintf(stderr, "[ERRO][%s:%s:%d]: ", __FILE__, __func__, __LINE__);\
    fprintf(stderr, __VA_ARGS__);\
} while (0)

#define kal_dbglog(...)\
do {\
    fprintf(stdout, "[INFO][%s:%s:%d]: ", __FILE__, __func__, __LINE__);\
    fprintf(stdout, __VA_ARGS__);\
} while (0)

#else

#define kal_dbglog_err(...)
#define kal_dbglog(...)

#endif // DEBUG

