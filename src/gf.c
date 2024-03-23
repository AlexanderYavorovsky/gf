#include <stdio.h>

#include "gf.h"
#include "poly.h"

void gf_free(gf_t ff)
{
    if (ff != NULL)
        poly_free(ff->poly);
    free(ff);
}

gf_t gf_init(uint8_t p, poly_t poly)
{
    gf_t ff;

    ff = malloc(sizeof(*ff));
    if (ff == NULL)
        return NULL;

    ff->p = p;
    ff->poly = poly_copy(poly);

    return ff;
}

void gf_elem_free(gf_elem_t el)
{
    if (el == NULL)
        return;
    poly_free(el->poly);
    free(el);
}

gf_elem_t gf_elem_from_array(uint8_t *arr, uint8_t n, gf_t ff)
{
    gf_elem_t el;
    poly_t tmp_poly;

    el = malloc(sizeof(*el));
    if (el == NULL)
        return NULL;
    
    tmp_poly = poly_init_from_array(arr, n);
    el->poly = poly_mod(tmp_poly, ff->poly, ff->p);
    el->ff = ff;

    poly_free(tmp_poly);

    return el;
}



/* ::remove */
void gf_print(gf_t ff)
{
    printf("FF: p:%u ", ff->p);
    poly_print(ff->poly);
}

/* ::remove */
void gf_elem_print(gf_elem_t el)
{
    printf("elem:\n  >>");
    gf_print(el->ff);
    printf("  >>");
    poly_print(el->poly);
}