#include "minunit.h"

#include "poly.h"

MU_TEST(test_init)
{
    uint8_t a[] = {1, 2, 3};
    poly_t f = poly_init_from_array(a, 3);

    mu_check(f->deg == 2);
    mu_check(f->coef[0] == 1);
    mu_check(f->coef[1] == 2);
    mu_check(f->coef[2] == 3);

    poly_free(f);
}

MU_TEST_SUITE(suite_init)
{
    MU_RUN_TEST(test_init);
}

MU_TEST(test_copy)
{
    uint8_t a[] = {1, 2, 3};
    poly_t f = poly_init_from_array(a, 3);
    poly_t g = poly_copy(f);

    mu_check(f->deg == g->deg);
    mu_check(f->coef[0] == g->coef[0]);
    mu_check(f->coef[1] == g->coef[1]);
    mu_check(f->coef[2] == g->coef[2]);

    poly_free(f);
    poly_free(g);
}

MU_TEST_SUITE(suite_copy)
{
    MU_RUN_TEST(test_copy);
}

int main()
{
    MU_RUN_SUITE(suite_init);
    MU_RUN_SUITE(suite_copy);

    MU_REPORT();

    return MU_EXIT_CODE;
}