#pragma once

#include <stdint.h>
#include <stdlib.h>

/* polynomial */
struct poly
{
    uint8_t deg; /* degree of the polynomial */
    uint8_t *coef; /* coefficients of the polynomial in little-endian */
};

typedef struct poly *poly_t;
typedef struct poly const *c_poly_t;

/* free up memory allocated for poly */
void poly_free(poly_t f);

/* get poly from array of coefficients */
poly_t poly_init_from_array(uint8_t *arr, size_t n);

/* return copy of poly f */
poly_t poly_copy(c_poly_t f);

/* normalize f's degree (skip leading zeroes) */
void poly_normalize(poly_t f);

/* return 1 if f = g, 0 otherwise */
int poly_isequal(c_poly_t f, c_poly_t g);

/* return 1 if f = 0, 0 otherwise */
int poly_iszero(c_poly_t f);


/* get g such that f + g = 0 (mod p) */
poly_t poly_neg(c_poly_t f, uint8_t p);

/* return f + g (mod p) */
poly_t poly_sum(c_poly_t a, c_poly_t b, uint8_t p);

/* return f - g (mod p) */
poly_t poly_subtract(c_poly_t a, c_poly_t b, uint8_t p);

/* return f * g (mod p) */
poly_t poly_multiply(c_poly_t a, c_poly_t b, uint8_t p);

/* return f % g (mod p) */
poly_t poly_mod(c_poly_t a, c_poly_t b, uint8_t p);


/* These "short" funcitons write the result of 
   the corresponding functions into a. 
   "v" stands for void return. */
void poly_vmul(poly_t *a, c_poly_t b, uint8_t p);
void poly_vmod(poly_t *a, c_poly_t b, uint8_t p);


/* return y such that x + y = 0 (mod p) */
uint8_t p_neg(uint8_t x, uint8_t p);

/* return y such that x * y = 1 (mod p) */
uint8_t p_inv(uint8_t x, uint8_t p);

/* return a + b (mod p) */
uint8_t p_sum(uint8_t a, uint8_t b, uint8_t p);

/* return a - b (mod p) */
uint8_t p_diff(uint8_t a, uint8_t b, uint8_t p);


/* get poly = 0 with `len` number of coefficients */
poly_t poly_get_zero(uint8_t len);

/* get poly = 1 with `len` number of coefficients */
poly_t poly_get_identity(uint8_t len);


/* return x to the n-th power */
uint64_t fastpow(uint8_t x, uint8_t n);

/* return x to the n-th power in Fp/(ir) */
poly_t poly_fastpow(c_poly_t x, uint8_t n, uint8_t p, c_poly_t ir);