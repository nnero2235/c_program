#ifndef _N_DEBUG_H
#define _N_DEBUG_H
#include<stdio.h>
#include<time.h>

extern int logLevel;
extern unsigned int testNum;
extern unsigned int testFail;

#define LOG_DEBUG 1
#define LOG_INFO 2
#define LOG_ERROR 3

static inline char *getNowTime(char *timeStr) {
    if(timeStr == NULL){
        return NULL;
    }
    time_t t;
    struct tm *localTime;
    t = time(NULL);
    localTime = localtime(&t);
    strftime(timeStr, 20, "%Y-%m-%d %H:%M:%S", localTime);
    return timeStr;
}


#define REAL_LOG(level, msg)                           \
    char *timeStr = malloc(20);                        \
    timeStr = getNowTime(timeStr);                     \
    printf("[%s] - [%s] : %s\n", level, timeStr, msg); \
    free(timeStr);

#define D_LOG(msg)              \
    if (logLevel <= LOG_DEBUG)  \
    {                           \
        REAL_LOG("Debug", msg); \
    }

#define I_LOG(msg)              \
    if (logLevel <= LOG_INFO)  \
    {                           \
        REAL_LOG("Info", msg); \
    }

#define E_LOG(msg)              \
    if (logLevel <= LOG_ERROR)  \
    {                           \
        REAL_LOG("Error", msg); \
    }

#define test_assert(msg, expr)             \
    do                                     \
    {                                      \
        testNum++;                         \
        printf("%d - %s", testNum, msg); \
        if (expr)                          \
            printf(" PASSED \n");          \
        else                               \
        {                                  \
            printf(" FAILED \n");          \
            testFail++;                        \
        }                                  \
    } while (0);

#define test_report()                                                           \
    do                                                                          \
    {                                                                           \
        if (testFail == 0)                                                          \
        {                                                                       \
            printf("Summary:%d tests -> All passed!\n", testNum);               \
        }                                                                       \
        else                                                                    \
        {                                                                       \
            printf("Summary:%d tests -> passed\n", testNum - testFail);             \
            printf("======== WARN ========\nWe have %d tests failed!\n", testFail); \
        }                                                                       \
        testNum = 0; \
        testFail = 0; \
    } while (0);

#endif