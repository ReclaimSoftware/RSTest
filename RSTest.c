#include <RSTest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void RTest_fail(char *message);

static uint64_t RTestNumTests = 0;
static char *RTestDescribeString = NULL;
static char *RTestTestString = NULL;
static struct timeval RTestT0;


void RTest_describe(char *str) {
    RTestDescribeString = str;
}


void RTest_startTest(char *str) {
    RTestTestString = str;
    RTestNumTests++;
}


void start_suite() {
    fprintf(stderr, "Running tests...\n");
    gettimeofday(&RTestT0, NULL);
}


void end_suite() {
    struct timeval RTestT1;
    gettimeofday(&RTestT1, NULL);
    int64_t microseconds = (
        ((RTestT1.tv_sec - RTestT0.tv_sec) * 1000000) +
        (RTestT1.tv_usec - RTestT0.tv_usec)
    );
    fprintf(stderr, "All %lld tests passed in %lld microseconds.\n",
                        (long long)RTestNumTests,
                        (long long)microseconds);
}


void RTest_fail(char *message) {
    if (RTestDescribeString || RTestTestString) {
        if (RTestDescribeString) {
            fprintf(stderr, "%s ", RTestDescribeString);
        }
        if (RTestTestString) {
            fprintf(stderr, "%s", RTestTestString);
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "\n");
    fprintf(stderr, "FAIL: %s\n", message);
    exit(1);
}


void assert_ints_equal(int64_t x, int64_t y) {
    if (x != y) {
        fprintf(stderr, "x: %lld\n", (long long)x);
        fprintf(stderr, "y: %lld\n", (long long)y);
        RTest_fail("ints differ");
    }
}


void assert_uints_equal(uint64_t x, uint64_t y) {
    if (x != y) {
        fprintf(stderr, "x: %llu\n", (unsigned long long)x);
        fprintf(stderr, "y: %llu\n", (unsigned long long)y);
        RTest_fail("uints differ");
    }
}


void assert_data_equal(uint8_t *x, uint8_t *y, uint32_t size) {
    if (!x) {
        RTest_fail("x is null");
    }
    if (!y) {
        RTest_fail("y is null");
    }
    if (memcmp(x, y, size) != 0) {
        for (uint32_t i = 0; i < size; i++) {
            if (x[i] == y[i]) {
                fprintf(stderr, "%02X %02X\n", x[i], y[i]);
            } else {
                fprintf(stderr, "%02X %02X <<<\n", x[i], y[i]);
            }
        }
        RTest_fail("byte strings differ");
    }
}


void assert_strings_equal(char *x, char *y) {
    if (!x) {
        RTest_fail("x is null");
    }
    if (!y) {
        RTest_fail("y is null");
    }
    if (strcmp(x, y) != 0) {
        fprintf(stderr, "x: '%s'\n", x);
        fprintf(stderr, "y: '%s'\n", y);
        RTest_fail("strings differ");
    }
}


void assert_one(int64_t x) {
    if (x != 1) {
        fprintf(stderr, "x: %lld\n", (long long)x);
        RTest_fail("expected one");
    }
}


void assert_zero(int64_t x) {
    if (x != 0) {
        fprintf(stderr, "x: %lld\n", (long long)x);
        RTest_fail("expected zero");
    }
}


void assert_null(char *x) {
    if (x) {
        fprintf(stderr, "x: '%s'\n", x);
        RTest_fail("expected NULL");
    }
}


FILE* assert_fopen(char *path, char *mode) {
    FILE *file = fopen(path, mode);
    if (!file) {
        RTest_fail("expected fopen to succeed");
    }
    return file;
}
