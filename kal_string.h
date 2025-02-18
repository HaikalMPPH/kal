#pragma once

#include "../types.h"

typedef struct kal_string_s kal_string_s;
struct kal_string_s {
    usize len;
    char* str;
};

kal_string_s
kal_string_init(
    const char* str
);

#ifdef KAL_DS_STRING_IMPL
// TODO
#endif
