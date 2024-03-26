#pragma once

#include "poly.h"

struct gf
{
    poly_t poly;
    uint8_t p;
};

typedef struct gf *gf_t;

struct gf_elem
{
    poly_t poly;
    gf_t ff;
};

typedef struct gf_elem *gf_elem_t;


extern gf_t gf2_8;
extern gf_t gf2_16;
extern gf_t gf2_32;


void gf_free(gf_t ff);

gf_t gf_init(uint8_t p, poly_t poly);

int gf_isequal(gf_t ff1, gf_t ff2);

gf_elem_t gf_get_zero(gf_t ff);

gf_elem_t gf_get_identity(gf_t ff);

gf_elem_t gf_neg(gf_elem_t x);

gf_elem_t gf_inv(gf_elem_t x);


gf_elem_t gf_sum(gf_elem_t a, gf_elem_t b);

gf_elem_t gf_subtract(gf_elem_t a, gf_elem_t b);

gf_elem_t gf_multiply(gf_elem_t a, gf_elem_t b);

gf_elem_t gf_div(gf_elem_t a, gf_elem_t b);



void gf_elem_free(gf_elem_t el);
gf_elem_t gf_elem_from_array(uint8_t *arr, uint8_t n, gf_t ff);


gf_elem_t uint8_to_gf_elem(uint8_t x);
uint8_t gf_elem_to_uint8(gf_elem_t x);

gf_elem_t uint16_to_gf_elem(uint16_t x);
uint16_t gf_elem_to_uint16(gf_elem_t x);

gf_elem_t uint32_to_gf_elem(uint32_t x);
uint32_t gf_elem_to_uint32(gf_elem_t x);

void gf_print(gf_t ff);
void gf_elem_print(gf_elem_t el);
