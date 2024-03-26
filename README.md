# Galois field library
## What is it
This is a static library in C which provides set of basic operations over elements of $GF(p)[x]/(r)$.

## Getting Started
### Requirements
* CMake (version 3.1 or higher)
* GCC

### Build
Clone this repository:
```
https://github.com/AlexanderYavorovsky/gf.git
```
Navigate to project directory:
```
cd gf
```
Make directory and run cmake:
``` 
mkdir build
cd build
cmake ..
make
```
The path to executable file will be: `build/tests/tests`


To test, run:
```
ctest
```

## Usage
This library provides following operations:
* `gf_sum`
* `gf_subtract`
* `gf_multiply`
* `gf_divide`
* `gf_neg`
* `gf_inv`
* `gf_get_zero`
* `gf_get_identity`

You can also convert `uint8_t`, `uint16_t`, `uint32_t` to element of `GF_{2^8}`, `GF_{2^16}` and `GF_{2^32}` correspondingly. For this purpose, use:
* `uint8_to_gf_elem`
* `gf_elem_to_uint8`
and so on.

### Example
```
uint8_t a[] = {1, 1, 1};
uint8_t b[] = {2, 1, 4, 3};
uint8_t c[] = {1, 0, 1};

poly_t r = poly_init_from_array(a, 3);
gf_t ff = gf_init(2, r);
gf_elem_t el1 = gf_elem_from_array(b, 4, ff);
gf_elem_t el2 = gf_elem_from_array(c, 3, ff);

gf_elem_t res = gf_sum(el1, el2);

poly_free(r);
gf_free(ff);
gf_elem_free(el1);
gf_elem_free(el2);
gf_elem_free(res);
```