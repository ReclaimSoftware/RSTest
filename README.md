**A minimal C test "framework".**

[![Build Status](https://secure.travis-ci.org/ReclaimSoftware/RSTest.png)](http://travis-ci.org/ReclaimSoftware/RSTest)


```c
#include <RSTest.h>

int main(...) {
    start_suite();

    DESCRIBE("Foo") {
      IT("bars") {
        ...
      }
    }

    end_suite();
    return 0;
}
```


### RSTest.h

```c
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
```

The only state under the hood:

- starting timestamp
- total number of tests so far
- current {describe,test} strings

When tests pass:

    Running tests...
    All 90 tests passed in 9 microseconds.


### [License: MIT](LICENSE.txt)
