#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "polynstruct.h"
#include "polynio.h"
#include "polynmath.h"

static Polynomial*  copyPolynomial(const Polynomial* polynomial)
{
    Polynomial * newPolynomial;
    newPolynomial = initPolynomial();
    if (NULL == newPolynomial)
        return NULL;
    newPolynomial->n = polynomial->n;
    newPolynomial->degree = polynomial->degree;
    int degrees[newPolynomial->n];
    double coefficients[newPolynomial->n];
    int i;
    for (i = 0; i < newPolynomial->n; i++)
    {
        degrees[i] = polynomial->monomials[i].degree;
        coefficients[i] = polynomial->monomials[i].coefficient;
    }
    newPolynomial->monomials = initMonomials(coefficients, degrees, newPolynomial->n);
    if (NULL == newPolynomial->monomials)
    {
        free(newPolynomial);
        return NULL;
    }
    return newPolynomial;
}

Polynomial*  polynNPow(const Polynomial *polynomial, const int n)
{
    assert(polynomial);
    assert(n > 0);

    Polynomial * tmp;
    Polynomial * tmp2 = (Polynomial *)polynomial;
    if (n == 1)
    {
        tmp = copyPolynomial(polynomial);
        if (NULL == tmp)
            return NULL;
        return tmp;
    }
    int i;
    for (i = 1; i < n; i++)
    {
        tmp = polynMult(tmp2, polynomial);

        if (i > 1)
            freePolynomial(&tmp2);

        if(NULL == tmp)
            return NULL;

        tmp2 = tmp;
    }
    if (EMEMORY == reductOrderPolynomial(tmp))
    {
        freePolynomial(&tmp);
        return NULL;
    }
    return tmp;
}

Polynomial*  polynSum(const Polynomial *polynomial1, const Polynomial *polynomial2)
{
    assert(polynomial1);
    assert(polynomial2);

    Polynomial *polynomial = NULL;
    polynomial = initPolynomial();
    if (NULL == polynomial)
        return NULL;

    // If polynomial1 has the monomial with biggest degree, we put that degree on polynomial->degree, else, it's the degree of polynomial2
    polynomial->degree = (polynomial1->degree > polynomial2->degree) ? polynomial1->degree : polynomial2->degree;
    polynomial->n = polynomial1->n + polynomial2->n;

    double   coefficients[polynomial->n];
    int     degrees[polynomial->n];
    int j;
    int i;
    for (i = 0; i < polynomial1->n; i++)
    {
        coefficients[i] = polynomial1->monomials[i].coefficient;
        degrees[i] = polynomial1->monomials[i].degree;
    }
    for (j = 0; j < polynomial2->n; j++)
    {
        coefficients[i] = polynomial2->monomials[j].coefficient;
        degrees[i] = polynomial2->monomials[j].degree;
        i++;
    }
    // if allocation and initialization of monomials don't work, free allocated polynomial and return NULL
    if ((polynomial->monomials = initMonomials(coefficients, degrees, polynomial->n)) == NULL)
    {
        freePolynomial(&polynomial);
        return NULL;
    }
    // reductOrderPolynomial(polynomial);
    if (EMEMORY == reductOrderPolynomial(polynomial))
    {
        freePolynomial(&polynomial);
        return NULL;
    }
    return polynomial;
}

Polynomial*  polynMult(const Polynomial *polynomial1, const Polynomial *polynomial2)
{
    assert(polynomial1);
    assert(polynomial2);

    Polynomial *polynomial = NULL;
    polynomial = initPolynomial();

    if (NULL == polynomial)
        return NULL;

    polynomial->n = polynomial1->n * polynomial2->n;
    polynomial->degree = polynomial1->monomials[0].degree + polynomial2->monomials[0].degree;

    double   coefficients[polynomial->n];
    int     degrees[polynomial->n];

    int i, j;
    int k = 0;
    // distributive property on the polynomials
    for (i = 0; i < polynomial1->n; i++)
    {
        for (j = 0; j < polynomial2->n; j++)
        {
            coefficients[k] = polynomial1->monomials[i].coefficient * polynomial2->monomials[j].coefficient;
            degrees[k] = polynomial1->monomials[i].degree + polynomial2->monomials[j].degree;
            k++;
        }
    }
    // if allocation and initialization of monomials don't work, free allocated polynomial and return NULL
    if ((polynomial->monomials = initMonomials(coefficients, degrees, polynomial->n)) == NULL)
    {
        freePolynomial(&polynomial);
        return NULL;
    }
    // REDUCT AND ORDER  the polynomial
    if (EMEMORY == reductOrderPolynomial(polynomial))
    {
        freePolynomial(&polynomial);
        return NULL;
    }
    return polynomial;
}

double  polynSolve(const Polynomial *polynomial, const int x)
{
    assert(polynomial);

    double res = 0;
    int i;

    for(i = 0; i < polynomial->n; i++)
    {
        res += solveMonomial(polynomial->monomials[i], x);
    }

    return res;
}

double  polynSolveHorner(const Polynomial *polynomial, const int x)
{
    assert(polynomial);
    assert(x);

    long double r = 0;
    int i = polynomial->degree;
    int tmp = 0;

    while (i >= 0)
    {
        while (polynomial->monomials[tmp].degree != i && i >= 0)
        {
            r = (r * x);
            i--;
        }
        if (polynomial->monomials[tmp].degree == i)
        {
            r = (r * x) + polynomial->monomials[tmp].coefficient;
            tmp++;
            i--;
        }
    }

    return r;
}

Polynomial*  polynDeriv(const Polynomial *polynomial)
{
    assert(polynomial);

    if (polynomial->degree == 0)
        return NULL;
    Polynomial *newPolynomial = NULL;
    newPolynomial = initPolynomial();
    if (NULL == polynomial)
        return NULL;

    int size = polynomial->n;

    if((polynomial->n > 1 && polynomial->monomials[size - 1].degree == 0) || (polynomial->monomials[0].degree == 0))
        size--;

    newPolynomial->n = size;
    newPolynomial->degree = polynomial->degree - 1;

    double   coefficients[size];
    int     degrees[size];

    int i;
    for(i = 0; i < polynomial->n; i++)
    {
        if(polynomial->monomials[i].degree == 0)
            break;
        coefficients[i] = polynomial->monomials[i].coefficient * polynomial->monomials[i].degree;
        degrees[i] = polynomial->monomials[i].degree - 1;
    }


    Monomial * monomial = initMonomials(coefficients, degrees, size);

    if (monomial == NULL)
    {
        freePolynomial(&newPolynomial);
        return NULL;
    }
    newPolynomial->monomials = monomial;

    return newPolynomial;
}

Polynomial*  polynDerivSum(const Polynomial *polynomial1, const Polynomial *polynomial2)
{
    assert(polynomial1);
    assert(polynomial2);

    Polynomial *polynomialDeriv1 = NULL;
    polynomialDeriv1 = polynDeriv(polynomial1);
    if (NULL == polynomialDeriv1)
        return NULL;
    Polynomial *polynomialDeriv2 = NULL;
    polynomialDeriv2 = polynDeriv(polynomial2);
    if (NULL == polynomialDeriv2)
    {
        freePolynomial(&polynomialDeriv1);
        return NULL;
    }

    Polynomial *polynomial = NULL;
    polynomial = polynSum(polynomialDeriv1, polynomialDeriv2);
    if (NULL == polynomial)
    {
        freePolynomial(&polynomialDeriv1);
        freePolynomial(&polynomialDeriv2);
        return NULL;
    }
    if (EMEMORY == reductOrderPolynomial(polynomial))
    {
        freePolynomial(&polynomial);
        return NULL;
    }
    return polynomial;
}

Polynomial*  polynDerivMult(const Polynomial *polynomial1, const Polynomial *polynomial2)
{
    assert(polynomial1);
    assert(polynomial2);

    Polynomial *polynomialDeriv1 = NULL;
    polynomialDeriv1 = polynDeriv(polynomial1);
    if (NULL == polynomialDeriv1)
        return NULL;
    Polynomial *polynomialDeriv2 = NULL;
    polynomialDeriv2 = polynDeriv(polynomial2);
    if (NULL == polynomialDeriv1)
    {
        freePolynomial(&polynomialDeriv1);
        return NULL;
    }

    Polynomial *polynomialMult1 = NULL;
    polynomialMult1 = polynMult(polynomialDeriv1, polynomial2);
    if (NULL == polynomialMult1)
    {
        freePolynomial(&polynomialDeriv1);
        freePolynomial(&polynomialDeriv2);
        return NULL;
    }
    Polynomial *polynomialMult2 = NULL;
    polynomialMult2 = polynMult(polynomial1, polynomialDeriv2);
    if (NULL == polynomialMult2)
    {
        freePolynomial(&polynomialDeriv1);
        freePolynomial(&polynomialDeriv2);
        freePolynomial(&polynomialMult1);
        return NULL;
    }

    Polynomial *polynomial = NULL;
    polynomial = polynSum(polynomialMult1, polynomialMult2);
    freePolynomial(&polynomialDeriv1);
    freePolynomial(&polynomialDeriv2);
    freePolynomial(&polynomialMult1);
    freePolynomial(&polynomialMult2);
    if (EMEMORY == reductOrderPolynomial(polynomial))
    {
        freePolynomial(&polynomial);
        return NULL;
    }
    return polynomial;
}

Polynomial*  polynPrimitive(const Polynomial *polynomial)
{
    assert(polynomial);

    Polynomial *newPolynomial = NULL;
    newPolynomial = initPolynomial();
    if (NULL == polynomial)
        return NULL;

    if (polynomial->n == 0)
        return newPolynomial;

    newPolynomial->n = polynomial->n + 1;
    newPolynomial->degree = polynomial->degree + 1;

    double   coefficients[newPolynomial->n];
    int     degrees[newPolynomial->n];

    int i;
    for(i = 0; i < polynomial->n; i++)
    {
        coefficients[i] = polynomial->monomials[i].coefficient / (polynomial->monomials[i].degree + 1);
        if (coefficients[i] < 0.01)
        {
            freePolynomial(&newPolynomial);
            return NULL;
        }
        degrees[i] = polynomial->monomials[i].degree + 1;
    }
    degrees[newPolynomial->n - 1] = 0;
    coefficients[newPolynomial->n - 1] = K;
    Monomial * monomial = initMonomials(coefficients, degrees, newPolynomial->n);

    if (monomial == NULL)
    {
        freePolynomial(&newPolynomial);
        return NULL;
    }
    newPolynomial->monomials = monomial;

    return newPolynomial;
}
