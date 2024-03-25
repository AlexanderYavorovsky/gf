#include "minunit.h"

#include "poly.h"
#include "gf.h"

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

MU_TEST(test_gf_init)
{
    uint8_t a[] = {1, 1, 1};
    poly_t f = poly_init_from_array(a, 3);
    gf_t ff = gf_init(2, f);

    mu_check(ff->p == 2);
    mu_check(poly_isequal(f, ff->poly));

    poly_free(f);
    gf_free(ff);

}

MU_TEST(test_el_init)
{
    uint8_t a[] = {1, 1, 1};
    uint8_t ac[] = {0};
    poly_t f = poly_init_from_array(a, 3);
    gf_t ff = gf_init(2, f);
    gf_elem_t el = gf_elem_from_array(a, 3, ff);
    poly_t act = poly_init_from_array(ac, 1);
    
    mu_check(poly_isequal(act, el->poly));

    poly_free(f);
    gf_free(ff);
    gf_elem_free(el);
    poly_free(act);
}

MU_TEST(test_el_init_remain)
{
    uint8_t a[] = {1, 1, 1};
    uint8_t b[] = {2, 1, 4, 3};
    uint8_t ac[] = {1, 1};
    poly_t f = poly_init_from_array(a, 3);
    gf_t ff = gf_init(2, f);
    gf_elem_t el = gf_elem_from_array(b, 4, ff);
    poly_t act = poly_init_from_array(ac, 2);
    
    mu_check(poly_isequal(act, el->poly));

    poly_free(f);
    gf_free(ff);
    gf_elem_free(el);
    poly_free(act);
}

MU_TEST_SUITE(suite_el_init)
{
    MU_RUN_TEST(test_el_init);
    MU_RUN_TEST(test_el_init_remain);
}

MU_TEST(test_gf_isequal_self)
{
    uint8_t a[] = {1, 1, 1};
    poly_t f = poly_init_from_array(a, 3);
    gf_t ff = gf_init(2, f);

    mu_check(gf_isequal(ff, ff));

    poly_free(f);
    gf_free(ff);
}

MU_TEST_SUITE(suite_gf_isequal)
{
    MU_RUN_TEST(test_gf_isequal_self);
}

MU_TEST(test_gf_get_zero)
{
    uint8_t a[] = {1, 1, 1};
    poly_t r = poly_init_from_array(a, 3);
    gf_t ff = gf_init(2, r);
    gf_elem_t zero = gf_get_zero(ff);

    mu_check(zero->poly->deg == 0);

    for (uint8_t i = 0; i <= zero->poly->deg; i++)
        mu_check(zero->poly->coef[i] == 0);

    poly_free(r);
    gf_free(ff);
    gf_elem_free(zero);
}

MU_TEST(test_gf_get_identity)
{
    uint8_t a[] = {1, 1, 1};
    poly_t r = poly_init_from_array(a, 3);
    gf_t ff = gf_init(2, r);
    gf_elem_t id = gf_get_identity(ff);

    mu_check(id->poly->deg == 0);
    mu_check(id->poly->coef[0] == 1);

    poly_free(r);
    gf_free(ff);
    gf_elem_free(id);
}

MU_TEST(test_gf_sum)
{
    uint8_t a[] = {1, 1, 1};
    uint8_t b[] = {2, 1, 4, 3};
    uint8_t c[] = {1, 0, 1};
    uint8_t ac[] = {1};
    
    poly_t r = poly_init_from_array(a, 3);
    gf_t ff = gf_init(2, r);
    gf_elem_t el1 = gf_elem_from_array(b, 4, ff);
    gf_elem_t el2 = gf_elem_from_array(c, 3, ff);
    gf_elem_t res = gf_sum(el1, el2);
    poly_t act = poly_init_from_array(ac, 1);

    mu_check(poly_isequal(act, res->poly));

    poly_free(r);
    gf_free(ff);
    gf_elem_free(el1);
    gf_elem_free(el2);
    gf_elem_free(res);
    poly_free(act);
}

MU_TEST_SUITE(suite_gf_sum)
{
    MU_RUN_TEST(test_gf_sum);
}

MU_TEST(test_gf_subtract)
{
    uint8_t a[] = {1, 1, 1};
    uint8_t b[] = {2, 1, 4, 3};
    uint8_t c[] = {1, 0, 1};
    uint8_t ac[] = {1};
    
    poly_t r = poly_init_from_array(a, 3);
    gf_t ff = gf_init(2, r);
    gf_elem_t el1 = gf_elem_from_array(b, 4, ff);
    gf_elem_t el2 = gf_elem_from_array(c, 3, ff);
    gf_elem_t res = gf_subtract(el1, el2);
    poly_t act = poly_init_from_array(ac, 1);

    mu_check(poly_isequal(act, res->poly));

    poly_free(r);
    gf_free(ff);
    gf_elem_free(el1);
    gf_elem_free(el2);
    gf_elem_free(res);
    poly_free(act);
}

MU_TEST_SUITE(suite_gf_subtract)
{
    MU_RUN_TEST(test_gf_subtract);
}

MU_TEST(test_gf_multiply)
{
    uint8_t a[] = {1, 1, 1};
    uint8_t b[] = {2, 1, 4, 3};
    uint8_t c[] = {1, 0, 1};
    uint8_t ac[] = {1};
    
    poly_t r = poly_init_from_array(a, 3);
    gf_t ff = gf_init(2, r);
    gf_elem_t el1 = gf_elem_from_array(b, 4, ff);
    gf_elem_t el2 = gf_elem_from_array(c, 3, ff);
    gf_elem_t res = gf_multiply(el1, el2);
    poly_t act = poly_init_from_array(ac, 1);

    mu_check(poly_isequal(act, res->poly));

    poly_free(r);
    gf_free(ff);
    gf_elem_free(el1);
    gf_elem_free(el2);
    gf_elem_free(res);
    poly_free(act);
}

MU_TEST_SUITE(suite_gf_multiply)
{
    MU_RUN_TEST(test_gf_multiply);
}

MU_TEST(test_poly_fastpow)
{
    uint8_t a[] = {1, 1, 1};
    uint8_t b[] = {1, 0, 1};
    uint8_t ac[] = {1, 1};
    
    poly_t r = poly_init_from_array(a, 3);
    poly_t x = poly_init_from_array(b, 3);
    poly_t res = poly_fastpow(x, 2, 2, r);
    poly_t act = poly_init_from_array(ac, 2);

    mu_check(poly_isequal(act, res));

    poly_free(r);
    poly_free(x);
    poly_free(res);
    poly_free(act);
}

MU_TEST(test_gf_neg)
{
    uint8_t a[] = {1, 1, 1};
    uint8_t b[] = {1, 0, 1};
    poly_t r = poly_init_from_array(a, 3);
    gf_t ff = gf_init(2, r);
    gf_elem_t x = gf_elem_from_array(b, 3, ff);
    gf_elem_t neg = gf_neg(x);
    gf_elem_t res = gf_sum(x, neg);
    gf_elem_t zero = gf_get_zero(ff);

    mu_check(poly_isequal(res->poly, zero->poly));

    poly_free(r);
    gf_free(ff);
    gf_elem_free(x);
    gf_elem_free(neg);
    gf_elem_free(res);
    gf_elem_free(zero);
}

MU_TEST(test_gf_inv)
{
    uint8_t a[] = {1, 1, 1};
    uint8_t b[] = {1, 0, 1};
    poly_t r = poly_init_from_array(a, 3);
    gf_t ff = gf_init(2, r);
    gf_elem_t x = gf_elem_from_array(b, 3, ff);
    gf_elem_t inv = gf_inv(x);
    gf_elem_t id = gf_get_identity(ff);
    gf_elem_t prod = gf_multiply(x, inv);

    mu_check(poly_isequal(id->poly, prod->poly));

    poly_free(r);
    gf_free(ff);
    gf_elem_free(x);
    gf_elem_free(inv);
    gf_elem_free(id);
    gf_elem_free(prod);
}

MU_TEST(test_gf_div)
{
    uint8_t a[] = {1, 1, 1};
    uint8_t b[] = {1, 0, 1, 1};
    uint8_t c[] = {0, 0, 1};
    uint8_t ac[] = {1};
    poly_t r = poly_init_from_array(a, 3);
    gf_t ff = gf_init(2, r);
    gf_elem_t el1 = gf_elem_from_array(b, 4, ff);
    gf_elem_t el2 = gf_elem_from_array(c, 3, ff);
    gf_elem_t res = gf_div(el1, el2);
    poly_t act = poly_init_from_array(ac, 1);

    mu_check(poly_isequal(res->poly, act));

    poly_free(r);
    gf_free(ff);
    gf_elem_free(el1);
    gf_elem_free(el2);
    gf_elem_free(res);
    poly_free(act);
}

MU_TEST_SUITE(suite_gf_div)
{
    MU_RUN_TEST(test_gf_div);
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
    MU_RUN_TEST(test_gf_init);
    MU_RUN_SUITE(suite_el_init);
    MU_RUN_SUITE(suite_gf_isequal);
    MU_RUN_TEST(test_gf_get_zero);
    MU_RUN_TEST(test_gf_get_identity);
    MU_RUN_SUITE(suite_gf_sum);
    MU_RUN_SUITE(suite_gf_subtract);
    MU_RUN_SUITE(suite_gf_multiply);
    MU_RUN_TEST(test_poly_fastpow);
    MU_RUN_TEST(test_gf_inv);
    MU_RUN_SUITE(suite_gf_div);
    MU_RUN_TEST(test_gf_neg);

    MU_REPORT();

    return MU_EXIT_CODE;
}