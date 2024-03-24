#include <string.h>
#include <stdio.h>

#include "poly.h"

static uint8_t mymax(uint8_t a, uint8_t b) { return a >= b ? a : b; }

void poly_free(poly_t f)
{
    if (f == NULL)
        return;
    free(f->coef);
    free(f);
}

poly_t poly_init_from_array(uint8_t *arr, size_t n)
{
    poly_t f;

    if (n == 0)
        return NULL;

    f = malloc(sizeof(*f));
    if (f == NULL) 
        return NULL;

    f->coef = malloc(sizeof(*f->coef) * n);
    if (f->coef == NULL)
    {
        poly_free(f);
        return NULL;
    }
    
    f->deg = n - 1;
    
    memcpy(f->coef, arr, sizeof(*f->coef) * n);
    
    return f;
}

poly_t poly_copy(poly_t f)
{
    poly_t g;

    if (f == NULL)
        return NULL;
    
    g = malloc(sizeof(*g));
    if (g == NULL)
        return NULL;

    g->deg = f->deg;

    g->coef = malloc(sizeof(*f->coef) * (f->deg + 1));
    if (g->coef == NULL) 
        return g;

    memcpy(g->coef, f->coef, (f->deg + 1) * sizeof(*f->coef));

    return g;
}

static void poly_normalize(poly_t f)
{
    uint8_t cnt = 0;
    if (f == NULL)
        return;

    for (cnt = 0; cnt < f->deg; cnt++)
        if (f->coef[f->deg - cnt] != 0)
            break;

    f->deg -= cnt;
}

int poly_isequal(c_poly_t f, c_poly_t g)
{
    if (f->deg != g->deg)
        return 0;

    return memcmp(f->coef, g->coef, f->deg + 1) == 0;
}

int poly_iszero(poly_t f)
{
    return f->deg == 0 && f->coef[0] == 0;
}

poly_t poly_neg(poly_t f, uint8_t p)
{
    poly_t res;

    if (f == NULL) 
        return NULL;
    
    res = malloc(sizeof(*res));
    if (res == NULL)
        return NULL;

    res->coef = malloc(f->deg * sizeof(res->coef));
    if (res->coef == NULL)
        return NULL;

    res->deg = f->deg;

    for (uint8_t i = 0; i <= f->deg; i++)
        res->coef[i] = (p - f->coef[i]) % p;

    poly_normalize(res);

    return res;
}

poly_t poly_sum(poly_t f, poly_t g, uint8_t p)
{
    poly_t res;
    uint8_t maxdeg;

    res = malloc(sizeof(*res));
    if (res == NULL)
        return NULL;

    maxdeg = mymax(f->deg, g->deg);
    res->coef = calloc(maxdeg, sizeof(res->coef));
    if (res->coef == NULL)
        return NULL;

    res->deg = maxdeg;

    for (uint8_t i = 0; i <= maxdeg; i++)
    {
        if (i <= f->deg)
            res->coef[i] += f->coef[i];
        if (i <= g->deg)
            res->coef[i] += g->coef[i];
        res->coef[i] %= p;
    }

    poly_normalize(res);

    return res;
}

poly_t poly_subtract(poly_t f, poly_t g, uint8_t p)
{
    poly_t gneg = poly_neg(g, p);
    poly_t res = poly_sum(f, gneg, p);

    poly_free(gneg);
    
    return res;
}

poly_t poly_multiply(poly_t f, poly_t g, uint8_t p)
{
    poly_t res;

    res = malloc(sizeof(*res));
    if (res == NULL)
        return NULL;
    
    res->coef = calloc(f->deg + g->deg + 2, sizeof(res->coef));
    if (res->coef == NULL)
        return NULL;

    res->deg = f->deg + g->deg;

    for (uint8_t i = 0; i <= f->deg; i++)
        for (uint8_t j = 0; j <= g->deg; j++)
            res->coef[i + j] = (f->coef[i] * g->coef[j] + res->coef[i + j]) % p;

    poly_normalize(res);

    return res;
}

poly_t poly_mod(poly_t f, poly_t g, uint8_t p)
{
    poly_t res;
    uint8_t m, n;
    uint8_t gn_inv;

    if (poly_iszero(g))
        return NULL;

    res = poly_copy(f);

    if (res->deg < g->deg)
        return res;

    m = f->deg;
    n = g->deg;
    gn_inv = p_inv(g->coef[n], p); /* inverse for n-th g coefficient */

    /* i, j are offsets from res leading (m-th) coefficient */
    for (uint8_t i = 0; i <= m - n; i ++) 
    {
        uint8_t q = (res->coef[m - i] * gn_inv) % p;
        for (uint8_t j = i; j <= n + i; j++)
        {
            uint8_t d = p_diff(res->coef[m - j], (q * g->coef[n - j + i]) % p, p);
            res->coef[m - j] = d;

            // printf("\n%u, %u) q:%u  d:%u\n", i, j, q, d);
            // poly_print(res);
        }
    }
    
    poly_normalize(res);

    return res;
}

uint8_t p_neg(uint8_t x, uint8_t p)
{
    return (p - x) % p;
}

uint8_t p_sum(uint8_t a, uint8_t b, uint8_t p)
{
    return (a + b) % p;
}

uint8_t p_diff(uint8_t a, uint8_t b, uint8_t p)
{
    return (a + p_neg(b, p)) % p;
}

uint8_t p_inv(uint8_t x, uint8_t p)
{
    return fastpow(x, p - 2) % p;
}

uint64_t fastpow(uint8_t x, uint8_t n)
{
    uint64_t res = 1;
    uint64_t mul = x;

    while (n > 0)
    {
        if (n % 2 != 0)
            res *= mul;
        mul *= mul;
        n >>= 1;
    }

    return res;
}

/* ::remove */
void poly_print(poly_t f)
{
    if (f == NULL) 
        return;

    printf("poly: ");
    for (size_t i = 0; i <= f->deg; i++)
        printf("%u ", f->coef[i]);

    printf("deg = %u\n", f->deg);
}