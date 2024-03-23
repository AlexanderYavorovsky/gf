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

void gf_free(gf_t ff);
gf_t gf_init(uint8_t p, poly_t poly);

void gf_elem_free(gf_elem_t el);
gf_elem_t gf_elem_from_array(uint8_t *arr, uint8_t n, gf_t ff);


void gf_print(gf_t ff);
void gf_elem_print(gf_elem_t el);
