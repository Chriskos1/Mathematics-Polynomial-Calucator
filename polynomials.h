#ifndef POLYNOMIALS_H_INCLUDED
#define POLYNOMIALS_H_INCLUDED

#include "polynstruct.h"
/** DEFINITION OF Polynomials TYPE THAT REPRESENT A STRUCTURE OF POLYNOMIALS */
typedef struct
{
    Polynomial **polynomialslList;
    int          n;
    int          cardinal;
}               Polynomials;

/**
NAME: printPolynomials - display polynomials
SYNOPSIS: Display all the polynomials on the structure
PARAMETERS:
    - Polynomials *polynomials: Structure Polynomials that contain the polynomials
RETURN: none
*/
void   printPolynomials(Polynomials *polynomials);


/**
NAME: freePolnyomials - free all polynomials
SYNOPSIS: Free the memory used by all polynomials of the list (and their monomials)
PARAMETERS:
    - Polynomials *polynomials: polynomials structure which contain the list of polynomials to free
RETURN: none
*/
void   freePolynomials(Polynomials *polynomials);


/**
NAME: freePolnyomials - free one polynomial
SYNOPSIS: Free the memory used by one polynomial of the list (and its monomials)
PARAMETERS:
    - Polynomials *polynomials: polynomials structure which contain the list of polynomials
RETURN: none
*/
void  freeOnePolynomial(Polynomials *polynomials, int i);


/**
NAME: addPolynomial - add a polynomial
SYNOPSIS: Add a polynomial to the array of polynomial in the structure polynomials
PARAMETERS:
    - Polynomials *polynomials: polynomials structure which contain the list of polynomials
    - polynomial *polynomial: The polynomial to add to the array
RETURN: status code
*/
int   addPolynomial(Polynomials *polynomials, Polynomial *newPolynomial);

#endif // POLYNOMIALS_H_INCLUDED
