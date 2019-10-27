#ifndef POLYNMATH_H_INCLUDED
#define POLYNMATH_H_INCLUDED

// Arbitrary constant for primitive calculation
static const double K = 2;

/** OPERATIONS ON POLYNOMIALS */

/**
NAME: polynNPow - N-th power of a polynomial
SYNOPSIS: Return a newly allocated polynomial set at the N-th power of the given one
PARAMETERS:
    - const Polynomial *polynomial: the polynomial that we will use for the calculation
    - const int n: the power to use for the calculation
NOTES:
    n must be positive (checked by assert)
RETURN: Newly allocated polynomial set as the N-th power
*/
Polynomial*  polynNPow(const Polynomial *polynomial, const int n);

/**
NAME: polynSum - sum of two polynomials
SYNOPSIS: Return a newly allocated polynomial set at the sum of the two given polynomials
PARAMETERS:
    - const Polynomial *polynomial1: the first polynomial that we will use for the calculation
    - const Polynomial *polynomial2: the second polynomial that we will use for the calculation
RETURN: Newly allocated polynomial set as the sum of the two polynomials
*/
Polynomial*  polynSum(const Polynomial *polynomial1, const Polynomial *polynomial2);

/**
NAME: polynSum - multiplication of two polynomials
SYNOPSIS: Return a newly allocated polynomial set as the multiplication of the two given polynomials
PARAMETERS:
    - const Polynomial *polynomial1: the first polynomial that we will use for the calculation
    - const Polynomial *polynomial2: the second polynomial that we will use for the calculation
RETURN: Newly allocated polynomial set as the multiplication of the two polynomials
*/
Polynomial*  polynMult(const Polynomial *polynomial1, const Polynomial *polynomial2);

/**
NAME: polynSolve - solve a polynomial
SYNOPSIS: Solve the polynomial with x and return the result
PARAMETERS:
    - const Polynomial *polynomial: the Polynomial structure to solve
    - const int x: the value to use to solve the monomial
RETURN: Result of the calculation
*/
double  polynSolve(const Polynomial *polynomial, const int x);

/**
NAME: polynSolveHorner - solve a polynomial (Horner)
SYNOPSIS: Solve the polynomial with x and return the result using the Horner method
PARAMETERS:
    - const Polynomial *polynomial: the Polynomial structure to solve
    - const int x: the value to use to solve the monomial
RETURN: Result of the calculation
*/
double  polynSolveHorner(const Polynomial *polynomial, const int x);

/**
NAME: polynDeriv - derivative of a polynomial
SYNOPSIS: Return a newly allocated polynomial set as the derivative of the given one
PARAMETERS:
    - const Polynomial *polynomial: the polynomial that we will use for the calculation
RETURN: Newly allocated polynomial set as the derivative of the polynomial
*/
Polynomial*  polynDeriv(const Polynomial *polynomial);

/**
NAME: polynDerivSum - sum/derivative of two polynomials
SYNOPSIS: Return a newly allocated polynomial set as the derivative of the sum of the given polynomials
PARAMETERS:
    - const Polynomial *polynomial1: the first polynomial that we will use for the calculation
    - const Polynomial *polynomial2: the second polynomial that we will use for the calculation
RETURN: Newly allocated polynomial set as the derivative of the sum of the given polynomials
*/
Polynomial*  polynDerivSum(const Polynomial *polynomial1, const Polynomial *polynomial2);

/**
NAME: polynDerivMult - multiplication/derivative of two polynomials
SYNOPSIS: Return a newly allocated polynomial set as the derivative of the multiplication of the two given polynomials
PARAMETERS:
    - const Polynomial *polynomial1: the first polynomial that we will use for the calculation
    - const Polynomial *polynomial2: the second polynomial that we will use for the calculation
RETURN: Newly allocated polynomial set as the derivative of the multiplication of the given polynomials
*/
Polynomial*  polynDerivMult(const Polynomial *polynomial1, const Polynomial *polynomial2);

/**
NAME: polynPrimitive - Primitive of a polynomial
SYNOPSIS: Return a newly allocated polynomial set as the primitive of the given polynomial
PARAMETERS:
    - const Polynomial *polynomial: the polynomial that we will use for the calculation
RETURN: Newly allocated polynomial set as the primitive of the given polynomial
*/
Polynomial*  polynPrimitive(const Polynomial *polynomial);

#endif // POLYNMATH_H_INCLUDED


