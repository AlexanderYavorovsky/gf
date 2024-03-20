#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    uint8_t deg;
    uint8_t *coef; /* little-endian */
} *poly_t;

void poly_free(poly_t f);

poly_t poly_init_from_array(uint8_t *arr, size_t n);

poly_t poly_copy(poly_t f);




/* ::remove */
void poly_print(poly_t f);