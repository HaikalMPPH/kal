#pragma once

#include "../types.h"

typedef struct kal_dynstr_s kal_dynstring_s;

struct kal_dynstring_s {
    char* str;
    usize len;
};
