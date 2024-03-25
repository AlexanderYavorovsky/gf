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

int gf_isequal(gf_t ff1, gf_t ff2)
{
    return ff1->p == ff2->p && poly_isequal(ff1->poly, ff2->poly);
}

gf_elem_t gf_get_zero(gf_t ff)
{
    gf_elem_t zero;

    zero = malloc(sizeof(*zero));
    if (zero == NULL) return NULL;

    zero->poly = poly_get_zero(ff->poly->deg + 1);
    zero->ff = ff;

    return zero;
}

gf_elem_t gf_get_identity(gf_t ff)
{
    gf_elem_t id;

    id = malloc(sizeof(*id));
    if (id == NULL) return NULL;

    id->poly = poly_get_identity(ff->poly->deg + 1);
    id->ff = ff;

    return id;
}

gf_elem_t gf_neg(gf_elem_t x)
{
    gf_elem_t neg;

    if ((neg = malloc(sizeof(*neg))) == NULL)
        return NULL;

    neg->ff = x->ff;
    neg->poly = poly_neg(x->poly, x->ff->p);

    return neg;
}

gf_elem_t gf_inv(gf_elem_t x)
{
    gf_elem_t inv;
    uint64_t pow;

    if (poly_iszero(x->poly)) 
        return NULL;

    if ((inv = malloc(sizeof(*inv))) == NULL)
        return NULL;
    
    inv->ff = x->ff;
    pow = fastpow(x->ff->p, x->ff->poly->deg) - 2;
    inv->poly = poly_fastpow(x->poly, pow, x->ff->p, x->ff->poly);

    return inv;
}

 gf_elem_t gf_sum(gf_elem_t a, gf_elem_t b)
 {
    gf_elem_t res;

    if (!gf_isequal(a->ff, b->ff))
        return NULL;

    res = malloc(sizeof(*res));
    if (res == NULL) 
        return NULL;
    
    res->ff = a->ff;
    res->poly = poly_sum(a->poly, b->poly, res->ff->p);

    return res;
 }

gf_elem_t gf_subtract(gf_elem_t a, gf_elem_t b)
{
    gf_elem_t res;
    
    if (!gf_isequal(a->ff, b->ff))
        return NULL;

    res = malloc(sizeof(*res));
    if (res == NULL) return NULL;

    res->ff = a->ff;
    res->poly = poly_subtract(a->poly, b->poly, res->ff->p);

    return res;
}

gf_elem_t gf_multiply(gf_elem_t a, gf_elem_t b)
{
    gf_elem_t res;
    poly_t tmp;

    if (!gf_isequal(a->ff, b->ff))
        return NULL;

    res = malloc(sizeof(*res));
    if (res == NULL) return NULL;

    res->ff = a->ff;
    tmp = poly_multiply(a->poly, b->poly, res->ff->p);
    res->poly = poly_mod(tmp, a->ff->poly, res->ff->p);

    poly_free(tmp);

    return res;
}

gf_elem_t gf_div(gf_elem_t a, gf_elem_t b)
{
    gf_elem_t res, b_inv;

    if (!gf_isequal(a->ff, b->ff) || poly_iszero(b->poly))
        return NULL;
    
    b_inv = gf_inv(b);
    res = gf_multiply(a, b_inv);

    gf_elem_free(b_inv);

    return res;
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