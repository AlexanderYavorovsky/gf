#include <stdint.h>
#include <stdlib.h>

struct poly
{
    uint8_t deg;
    uint8_t *coef; /* little-endian */
};

typedef struct poly *poly_t;

void poly_free(poly_t f);

poly_t poly_init_from_array(uint8_t *arr, size_t n);

poly_t poly_copy(poly_t f);

int poly_isequal(poly_t f, poly_t g);

poly_t poly_neg(poly_t f, uint8_t p);

poly_t poly_sum(poly_t f, poly_t g, uint8_t p);

poly_t poly_subtract(poly_t f, poly_t g, uint8_t p);

poly_t poly_multiply(poly_t f, poly_t g, uint8_t p);


/* ::remove */
void poly_print(poly_t f);
