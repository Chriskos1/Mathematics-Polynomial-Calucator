#ifndef POLYNSTRUCT_H_INCLUDED
#define POLYNSTRUCT_H_INCLUDED
#include "monomial.h"

/** DEFINITION OF Polynomial TYPE THAT REPRESENT A POLYNOMIAL */
typedef struct
{
    Monomial *  monomials;
    int         degree;
    int         n;
}               Polynomial;


/** STRUCTURE OF THE POLYNOMIAL */

/**
NAME: initPolynomial - allocate and init a polynomial
SYNOPSIS: Allocate, initialize to 0 and return a new polynomial structure
PARAMETERS: none
RETURN: The new polynomial, NULL on allocation error
*/
Polynomial* initPolynomial(void);

/**
NAME: freePolnyomial - free a polynomial
SYNOPSIS: Free the memory used by the given polynomial and its monomials
PARAMETERS:
    - Polynomial **polynomial: pointer to the address of the polynomial
RETURN: none
*/
void        freePolynomial(Polynomial **polynomial);

/**
NAME: freePolnyomial - reduct/order the given polynomial
SYNOPSIS: Reduct and order the given polynomial in descending order of degree
PARAMETERS:
    - Polynomial *polynomial: address of the polynomial
RETURN: status code (cf. POLYNIO_ERRORS)
*/
int        reductOrderPolynomial(Polynomial *polynomial);

/**
NAME: reductPolynomial - reduct polynomial
SYNOPSIS: Reduct the given polynomial
PARAMETERS:
    - Polynomial *polynomial: address of the polynomial
RETURN: status code (cf. POLYNIO_ERRORS)
*/
int         reductPolynomial(Polynomial *polynomial);

/**
NAME: orderPolynomial - order polynomial
SYNOPSIS: Order the given polynomial in descending order of degree
PARAMETERS:
    - Polynomial *polynomial: address of the polynomial
RETURN: none
*/
void        orderPolynomial(Polynomial *polynomial);

#endif // POLYNSTRUCT_H_INCLUDED
