#ifndef __RSTest_h__
#define __RSTest_h__

#include <stdint.h>
#include <stdio.h>


#define DESCRIBE(str)   RTest_describe(str);
#define IT(str)         RTest_startTest(str);
#define TEST(str)       RTest_startTest(str);


void start_suite();
void end_suite();


void assert_ints_equal(int64_t x, int64_t y);
void assert_uints_equal(uint64_t x, uint64_t y);
void assert_data_equal(uint8_t *x, uint8_t *y, uint32_t size);
void assert_strings_equal(char *x, char *y);
void assert_one(int64_t x);
void assert_zero(int64_t x);
void assert_null(char *x);
FILE* assert_fopen(char *path, char *mode);


void RTest_describe(char *str);
void RTest_startTest(char *str);


#endif