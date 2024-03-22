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

MU_TEST(test_poly_sum)
{
    uint8_t a[] = {3, 2, 3};
    uint8_t b[] = {3, 4, 2};
    poly_t f = poly_init_from_array(a, 3);
    poly_t g = poly_init_from_array(b, 3);

    poly_t res = poly_sum(f, g, 5);

    mu_check(res->deg == 1);
    mu_check(res->coef[0] == 1);
    mu_check(res->coef[1] == 1);

    poly_free(f);
    poly_free(g);
    poly_free(res);
}

MU_TEST_SUITE(suite_poly_sum)
{
    MU_RUN_TEST(test_poly_sum);
}

MU_TEST(test_poly_noteq)
{
    uint8_t a[] = {3, 2, 3};
    uint8_t b[] = {3, 4, 2};
    poly_t f = poly_init_from_array(a, 3);
    poly_t g = poly_init_from_array(b, 3);

    mu_check(!poly_isequal(f, g));

    poly_free(f);
    poly_free(g);
}

MU_TEST(test_poly_eq)
{
    uint8_t a[] = {3, 2, 3};
    poly_t f = poly_init_from_array(a, 3);

    mu_check(poly_isequal(f, f));

    poly_free(f);
}

MU_TEST_SUITE(suite_poly_eq)
{
    MU_RUN_TEST(test_poly_eq);
    MU_RUN_TEST(test_poly_noteq);
}

MU_TEST(test_poly_neg)
{
    uint8_t a[] = {2, 1, 3};
    uint8_t b[] = {3, 4, 2};
    poly_t g = poly_init_from_array(b, 3);

    poly_t res = poly_neg(g, 5);
    poly_t act = poly_init_from_array(a, 3);

    mu_check(poly_isequal(act, res));

    poly_free(act);
    poly_free(g);
    poly_free(res);
}

MU_TEST_SUITE(suite_poly_neg)
{
    MU_RUN_TEST(test_poly_neg);
}

MU_TEST(test_poly_sub)
{
    uint8_t a[] = {3, 2, 3};
    uint8_t b[] = {3, 4, 2};
    poly_t f = poly_init_from_array(a, 3);
    poly_t g = poly_init_from_array(b, 3);

    poly_t res = poly_sum(f, g, 5);

    mu_check(res->deg == 1);
    mu_check(res->coef[0] == 1);
    mu_check(res->coef[1] == 1);

    poly_free(f);
    poly_free(g);
    poly_free(res);
}

MU_TEST_SUITE(suite_poly_sub)
{
    MU_RUN_TEST(test_poly_sub);
}

MU_TEST(test_poly_mul)
{
    uint8_t a[] = {3, 2, 3};
    uint8_t b[] = {3, 4, 2};
    uint8_t ac[] = {4, 3, 3, 1, 1};
    poly_t f = poly_init_from_array(a, 3);
    poly_t g = poly_init_from_array(b, 3);
    poly_t res = poly_multiply(f, g, 5);
    poly_t act = poly_init_from_array(ac, 5);
    
    mu_check(poly_isequal(act, res));

    poly_free(f);
    poly_free(g);
    poly_free(res);
    poly_free(act);
}

MU_TEST_SUITE(suite_poly_mul)
{
    MU_RUN_TEST(test_poly_mul);
}

MU_TEST(test_inv)
{
    mu_check(p_inv(3, 5) == 2);
    mu_check(p_inv(2, 5) == 3);
    mu_check(p_inv(4, 7) == 2);
}

MU_TEST(test_poly_mod2)
{
    uint8_t a[] = {1, 1};
    uint8_t b[] = {1, 1, 1};
    poly_t f = poly_init_from_array(a, 2);
    poly_t g = poly_init_from_array(b, 3);
    poly_t res = poly_mod(f, g, 2);
    poly_t act = poly_init_from_array(a, 2);

    mu_check(poly_isequal(act, res));

    poly_free(f);
    poly_free(g);
    poly_free(res);
    poly_free(act);
}

MU_TEST(test_poly_mod_self)
{
    uint8_t a[] = {1, 1};
    poly_t f = poly_init_from_array(a, 2);
    poly_t res = poly_mod(f, f, 2);

    mu_check(poly_iszero(res));

    poly_free(f);
    poly_free(res);
}

MU_TEST(test_poly_mod5_remain)
{
    uint8_t a[] = {2, 3, 3};
    uint8_t b[] = {3, 2};
    uint8_t ac[] = {3};
    poly_t f = poly_init_from_array(a, 3);
    poly_t g = poly_init_from_array(b, 2);
    poly_t res = poly_mod(f, g, 5);
    poly_t act = poly_init_from_array(ac, 1);

    mu_check(poly_isequal(act, res));

    poly_free(f);
    poly_free(g);
    poly_free(res);
    poly_free(act);
}

MU_TEST(test_poly_mod7_remain)
{
    uint8_t a[] = {3, 0, 1, 0, 2, 4};
    uint8_t b[] = {1, 0, 1, 3};
    uint8_t ac[] = {1, 6};
    poly_t f = poly_init_from_array(a, 6);
    poly_t g = poly_init_from_array(b, 4);
    poly_t res = poly_mod(f, g, 7);
    poly_t act = poly_init_from_array(ac, 2);

    mu_check(poly_isequal(act, res));

    poly_free(f);
    poly_free(g);
    poly_free(res);
    poly_free(act);
}

MU_TEST_SUITE(suite_poly_mod)
{
    MU_RUN_TEST(test_poly_mod2);
    MU_RUN_TEST(test_poly_mod_self);
    MU_RUN_TEST(test_poly_mod5_remain);
    MU_RUN_TEST(test_poly_mod7_remain);
}

int main()
{
    MU_RUN_SUITE(suite_init);
    MU_RUN_SUITE(suite_copy);
    MU_RUN_SUITE(suite_poly_sum);
    MU_RUN_SUITE(suite_poly_eq);
    MU_RUN_SUITE(suite_poly_neg);
    MU_RUN_SUITE(suite_poly_sub);
    MU_RUN_SUITE(suite_poly_mul);
    MU_RUN_TEST(test_inv);
    MU_RUN_SUITE(suite_poly_mod);

    MU_REPORT();

    return MU_EXIT_CODE;
}