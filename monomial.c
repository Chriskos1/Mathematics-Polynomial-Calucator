#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "monomial.h"
#include "polynstruct.h"

void        freeMonomials(Monomial **monomial)
{
    assert(monomial);

    free(*monomial);
    *monomial = NULL;
}

Monomial    *initMonomials(const double *coefficients, const int *degrees, const int n)
{
    assert(coefficients);
    assert(degrees);
    assert(n);

    Monomial * monomials = NULL;

    monomials = malloc(n * sizeof(Monomial));
    if (NULL == monomials)
        return NULL;

    int i;
    for (i = 0; i < n; i++)
    {
        monomials[i].degree = degrees[i];
        monomials[i].coefficient = coefficients[i];
    }
    return monomials;

}

void        printMonomial(const Monomial monomial, FILE * fd)
{
    fprintf(fd, "(%.2f, %d)", monomial.coefficient, monomial.degree);
}

double      solveMonomial(const Monomial monomial, const int x)
{
    double result = x;

    if (monomial.degree == 0)
        result = 1;
    if (monomial.degree == 2)
    {
        result = result * result;
    }
    else if(monomial.degree >= 3)
    {
        result = pow(x, monomial.degree);
    }
    result = result * monomial.coefficient;

    return result;
}
