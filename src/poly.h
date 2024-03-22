#pragma once

#include <stdint.h>
#include <stdlib.h>

struct poly
{
    uint8_t deg;
    uint8_t *coef; /* little-endian */
};

typedef struct poly *poly_t;
typedef struct poly const *c_poly_t;

void poly_free(poly_t f);

poly_t poly_init_from_array(uint8_t *arr, size_t n);

poly_t poly_copy(poly_t f);

int poly_isequal(c_poly_t f, c_poly_t g);

int poly_iszero(poly_t f);


poly_t poly_neg(poly_t f, uint8_t p);

poly_t poly_sum(poly_t f, poly_t g, uint8_t p);

poly_t poly_subtract(poly_t f, poly_t g, uint8_t p);

poly_t poly_multiply(poly_t f, poly_t g, uint8_t p);

poly_t poly_mod(poly_t f, poly_t g, uint8_t p);


uint8_t p_neg(uint8_t x, uint8_t p);

uint8_t p_sum(uint8_t a, uint8_t b, uint8_t p);

uint8_t p_diff(uint8_t a, uint8_t b, uint8_t p);

uint8_t p_inv(uint8_t x, uint8_t p);

uint64_t fastpow(uint8_t x, uint8_t n);


/* ::remove */
void poly_print(poly_t f);
