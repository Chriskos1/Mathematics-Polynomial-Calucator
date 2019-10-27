#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "monomial.h"
#include "polynstruct.h"
#include "polynio.h"


Polynomial* initPolynomial(void)
{
    Polynomial *polynomial = NULL;

    polynomial = malloc(sizeof(Polynomial));
    if (NULL == polynomial)
        return NULL;
    polynomial->monomials = NULL;
    polynomial->degree = 0;
    polynomial->n = 0;
    return polynomial;
}

void        freePolynomial(Polynomial **polynomial)
{
    assert(polynomial);

    if (NULL != &((*polynomial)->monomials))
        freeMonomials(&((*polynomial)->monomials));
    free(*polynomial);
    polynomial = NULL;
}

int        reductOrderPolynomial(Polynomial *polynomial)
{
    int ret;

    orderPolynomial(polynomial);
    ret = reductPolynomial(polynomial);
    if (ret == EMEMORY)
        return EMEMORY;
    return SUCCESS;
}

int        reductPolynomial(Polynomial *polynomial)
{
    int i = 0;
    int nbMonomials = 0;
    int tmp;

    double coefficients[polynomial->degree + 1];
    int degrees[polynomial->degree + 1];
    while (i < polynomial->n)
    {
        tmp = polynomial->monomials[i].degree;

        coefficients[nbMonomials] = 0;
        degrees[nbMonomials] = tmp;
        while (polynomial->monomials[i].degree == tmp)
        {
            coefficients[nbMonomials] += polynomial->monomials[i].coefficient;
            i++;
        }
        nbMonomials++;
    }
    Monomial *monomials = NULL;
    monomials = initMonomials(coefficients, degrees, nbMonomials);
    if (NULL == monomials)
    {
        freePolynomial(&polynomial);
        return EMEMORY;
    }
    freeMonomials(&(polynomial->monomials));
    polynomial->monomials = monomials;
    polynomial->n = nbMonomials;
    return SUCCESS;
}

static int compareMonomials(const void *monomial1, const void *monomial2)
{
    assert(monomial1);
    assert(monomial2);

    Monomial *tmp1 = NULL;
    Monomial *tmp2 = NULL;
    tmp1 = (Monomial *)monomial1;
    tmp2 = (Monomial *)monomial2;

    return (tmp2->degree - tmp1->degree);
}

void        orderPolynomial(Polynomial *polynomial)
{
    qsort(polynomial->monomials, polynomial->n, sizeof(Monomial), compareMonomials);
}
