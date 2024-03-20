#include <string.h>
#include <stdio.h>

#include "poly.h"

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

    f->coef = malloc(sizeof(f->coef) * n);
    if (f->coef == NULL)
    {
        poly_free(f);
        return NULL;
    }
    
    f->deg = n - 1;
    
    memcpy(f->coef, arr, sizeof(f->coef) * n);
    
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

    g->coef = malloc(sizeof(f->coef) * (f->deg + 1));
    if (g->coef == NULL) 
        return g;

    memcpy(g->coef, f->coef, sizeof(f->coef) * (f->deg + 1));

    return g;
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