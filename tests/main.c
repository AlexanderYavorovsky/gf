#include "minunit.h"
#include <stdio.h>

MU_TEST(test_test)
{
    mu_check(1 == 1);
}

MU_TEST(test2)
{
    mu_check(0 == 0);
}

MU_TEST(test3)
{
    mu_check(3 == 3);
}

int main()
{
    MU_RUN_TEST(test_test);
    MU_RUN_TEST(test2);
    MU_RUN_TEST(test3);

    MU_REPORT();
    return MU_EXIT_CODE;
}