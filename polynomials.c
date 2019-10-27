#include <stdio.h>
#include <stdlib.h>
#include "polynomials.h"
#include "polynstruct.h"
#include "polynio.h"

void   printPolynomials(Polynomials *polynomials)
{
    int i;

    for(i = 0; i < polynomials->cardinal; i++)
    {
        printf("%d) ", i + 1);
        printPolynomial(polynomials->polynomialslList[i], NULL);
    }
}

void   freePolynomials(Polynomials *polynomials)
{
    int i;

    for (i = polynomials->cardinal - 1; i >= 0; i--)
    {
        freePolynomial(&(polynomials->polynomialslList[i]));
    }
    polynomials->cardinal = 0;
}

void  freeOnePolynomial(Polynomials *polynomials, int i)
{
    freePolynomial(&(polynomials->polynomialslList[i - 1]));
    polynomials->polynomialslList[i - 1] = NULL;
    while (i < polynomials->cardinal)
    {
        polynomials->polynomialslList[i - 1] = polynomials->polynomialslList[i];
        i++;
    }
    polynomials->cardinal--;
}

int   addPolynomial(Polynomials *polynomials, Polynomial *newPolynomial)
{
    int CONSTANT = 10;
    if (polynomials->cardinal == polynomials->n)
    {
        Polynomial **pList = NULL;
        pList = realloc(polynomials->polynomialslList, sizeof(Polynomial*) * (polynomials->n + CONSTANT));
        if (NULL == pList)
            return EMEMORY;
        polynomials->polynomialslList = pList;
    }
    polynomials->polynomialslList[polynomials->cardinal] = newPolynomial;
    polynomials->cardinal ++;
    return SUCCESS;
}
