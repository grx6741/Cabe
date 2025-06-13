#pragma once

#include <stdio.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <variant>

#define CABE_TODO                                                                                                      \
    do                                                                                                                 \
    {                                                                                                                  \
        printf("%s:%d %s is not implemented\n", __FILE__, __LINE__, __func__);                                         \
    } while (0)

#define CABE_MEM_CHECK(p)                                                                                              \
    do                                                                                                                 \
    {                                                                                                                  \
        if (!(p))                                                                                                      \
            CABE_LOG_DEBUG("Memory Allocation Failed! Not Enough RAM?");                                               \
    } while (0)

#define CABE_LOG(...) printf("[CABE] : " __VA_ARGS__)

#ifdef DEBUG
#define CABE_LOG_DEBUG(...) printf("[DEBUG] : " __VA_ARGS__)
#else
#define CABE_LOG_DEBUG(...)
#endif