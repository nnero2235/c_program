#ifndef _TEST_HELPER_H
#define _TEST_HELPER_H

unsigned int testNum = 0;
unsigned int fail = 0;

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
            fail++;                        \
        }                                  \
    } while (0);

#define test_report()                                                         \
    do                                                                        \
    {                                                                         \
        if (fail == 0)                                                        \
        {                                                                     \
            printf("Summary:%d tests -> All passed!\n", testNum);             \
        }                                                                     \
        else                                                                  \
        {                                                                     \
            printf("Summary:%d tests -> passed\n", testNum - fail);           \
            printf("======== WARN ========\nWe have %d tests failed!\n", fail); \
        }                                                                     \
    } while (0);

#endif