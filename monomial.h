#ifndef MONOMIAL_H_INCLUDED
#define MONOMIAL_H_INCLUDED

/** DEFINITION OF Monomial TYPE THAT REPRESENT MONOMIAL */
typedef struct  Monomial
{
    double      coefficient;
    int         degree;
}               Monomial;


/** MANIPULATION ON MONOMIAL */

/**
NAME: freeMonomials - free an array of monomials
SYNOPSIS: Free memory used by the array of monomial given by pointer
PARAMETERS:
    - Monomial **monomial: the pointer of the array of monomials to free
RETURN: none
*/
void        freeMonomials(Monomial **monomial);


/**
NAME: initMonomials - init an array of monomials
SYNOPSIS: Allocation and initialization of an array of
          monomials with the coefficients and degrees given
PARAMETERS:
    - const double *coefficients: an array with all coefficients
    - const int *degrees: an array with all degrees (order must match with coefficients array)
    - const int n: number of monomials
RETURN: The array of monomials, NULL on allocation error
*/
Monomial    *initMonomials(const double *coefficients, const int *degrees, const int n);

/**
NAME: printMonomial - display monomial value
SYNOPSIS: Display monomial value to stdin
PARAMETERS:
    - const Monomial monomial: the monomial structure to print
    - int fd: file descriptor to write on
FORMAT: (x, y)
    x is the coefficient of the monomial structure
    y is the degree of the monomial structure
RETURN: none
*/
void        printMonomial(const Monomial  monomial, FILE * fd);

/**
NAME: printMonomial - solve the monomial
SYNOPSIS: Solve the monomial with x and return the result
PARAMETERS:
    - const Monomial monomial: the monomial structure to solve
    - const int x: the value to use to solve the monomial
RETURN: Result of the calculation
*/
double      solveMonomial(const Monomial monomial, const int x);

#endif // MONOMIAL_H_INCLUDED
