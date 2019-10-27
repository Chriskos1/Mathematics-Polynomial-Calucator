#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "monomial.h"
#include "polynstruct.h"
#include "polynio.h"

void cleanStdin()
{
    char c;
    while((c = getchar()) != '\n' && c != EOF)
        ;
}

int     readPolynomial(Polynomial **polynomial, const double *coefficients, const int *degrees, const int n)
{
    assert(polynomial);
    assert(coefficients);
    assert(degrees);
    assert(n);

    *polynomial = initPolynomial();
    if (NULL == *polynomial)
        return EMEMORY;

    (*polynomial)->monomials = initMonomials(coefficients, degrees, n);
    if (NULL == ((*polynomial)->monomials))
    {
        freePolynomial(polynomial);
        return EMEMORY;
    }
    (*polynomial)->n = n;
    (*polynomial)->degree = degrees[0];

    return SUCCESS;
}

int     readPolynomialStdin(Polynomial **polynomial)
{
    assert(polynomial);

    printf("CREATION OF A NEW POLYNOMIAL:\n");
    *polynomial = initPolynomial();
    if (NULL == *polynomial)
        return EMEMORY;

    int n = 0;
    do
    {
        printf("How many monomials in the polynomial? ");
        scanf("%d", &n);
        cleanStdin();
    }
    while (n <= 0);
    (*polynomial)->n = n;

    int degrees[n];
    double coefficients[n];
    double coeff;
    int degree;
    int i = 0;
    printf("Monomials will be defined in descending order of degree\n");
    do
    {
        printf("Monomial %d\n", i + 1);
        do
        {
            printf("\tCoefficient: ");
            scanf("%lf", &coeff);
            cleanStdin();
        }
        while (-0.0000000001 <= coeff && coeff <= 0.0000000001);
        coefficients[i] = coeff;
        do
        {
            printf("\tDegree: ");
            scanf("%d", &degree);
            cleanStdin();
        }
        /* Loop while:
            - Degree is negative
            - Degree is too big (same as last degree or biggest)
            - Degree is too small (other monomials could not be set if the current is too small
        */
        while (degree < 0 || (i > 0 && degree >= degrees[i -1]) || (degree < (n - i - 1)));
        degrees[i] = degree;

        i++;
    }
    while (i < n);

    (*polynomial)->degree = degrees[0];
    (*polynomial)->monomials = initMonomials(coefficients, degrees, n);
    if (NULL == (*polynomial)->monomials)
    {
        freePolynomial(polynomial);
        return EMEMORY;
    }
    return SUCCESS;
}

/** nbMonomes: function that count the number of monomes in a polynomial */
static int nbMonomes(const char *buff)
{
    int i = 1;
    int monomes = 0;

    // count number of opening parenthesis to know the number of monomials
    // begin at 1 because 0 is an opening parenthesis for the Polynomial and not for a monomial in it
    while(buff[i])
    {
        if (buff[i] == '(')
            monomes++;
        i++;
    }
    return monomes;
}

/** checkPolynome: function that check the format of the Polynome in the file */
static int checkPolynome(const char *buff)
{
    int i = 1;
    if (buff[0] != '(')
        return EWFORMAT;
    while (buff[i] != '\n' && buff[i] != '\0')
    {
        if (buff[i] != '(')
            return EWFORMAT;
        //  this check is only for coefficient because degree must be positive
        if (buff[i + 1] == '-')
            i++;
        if (!(buff[++i] <= '9' && buff[i] >= '0'))
            return EWFORMAT;
        while (buff[i] <= '9' && buff[i] >= '0')
            i++;
        // check because we have a double for coefficient
        if (buff[i++] == '.')
        {
            while (buff[i] >= '0' && buff[i] <= '9')
                i++;
        }
        if (buff[i] == '\n' || buff[i] == '\0')
            return SUCCESS;
        if (buff[i] != ',' || buff[++i] != ' ')
            return EWFORMAT;
        if (!(buff[++i] <= '9' && buff[i] >= '0'))
            return EWFORMAT;
        while (buff[i] <= '9' && buff[i] >= '0')
            i++;
        if (buff[i++] != ')')
            return EWFORMAT;
        if (!(buff[i++] == ')' && (buff[i] == '\n' || buff[i] == '\0')) && !(buff[i - 1] == ',' && buff[i++] == ' '))
            return EWFORMAT;
        if (buff[i] == '\n' || buff[i] == '\0')
            return SUCCESS;
    }
    return SUCCESS;
}

int     readPolynomialFile(Polynomial **polynomial, const char *file)
{
    assert(polynomial);
    assert(file);

    FILE * fp;
    char buff[1000];

    if ((fp = fopen (file, "r")) == NULL)
        return EOPEN;
    fgets(buff, 1000, fp);
    fclose(fp);
    int ret;
    // Check only Format for the moment
    ret = checkPolynome(buff);
    if (ret == EWFORMAT)
        return EWFORMAT;
    *polynomial = initPolynomial();
    if (NULL == *polynomial)
        return EMEMORY;

    int n;
    n = nbMonomes(buff);

    (*polynomial)->n = n;

    int degrees[n];
    double coefficients[n];

    int monome = 0;
    int i = 2;
    char coeff[20];
    char degree[20];
    int j;
    // Loop through the buffer to get the coefficients and degrees
    while (monome < n)
    {
        j = 0;
        if (buff[i] == '-')
        {
            coeff[j] = '-';
            i++;
            j++;
        }
        while (buff[i] >= '0' && buff[i] <= '9')
        {
            coeff[j] = buff[i];
            j++;
            i++;
        }
        // that check is because coefficient is a double
        coeff[j++] = '.';
        if (buff[i++] == '.')
        {
            while (buff[i] >= '0' && buff[i] <= '9')
            {
                coeff[j] = buff[i];
                j++;
                i++;
            }
        }
        coeff[j] = '\0';
        coefficients[monome] = atof(coeff);
        if (0.0e-10 >= coefficients[monome] && coefficients[monome] <= -0.0e-10)
        {
            freePolynomial(polynomial);
            return EMATH;
        }
        j = 0;
        // skip the space and the parenthesis
        i += 2;
        while (buff[i] >= '0' && buff[i] <= '9')
        {
            degree[j] = buff[i];
            j++;
            i++;
        }
        degree[j] = '\0';
        degrees[monome] = atoi(degree);
        if (degrees[monome] < 0 || (monome > 0 && degrees[monome] >= degrees[monome - 1]) || (degrees[monome] < (n - monome - 1)))
        {
            freePolynomial(polynomial);
            return EMATH;
        }
        monome++;
        // skip the parenthesis, comma, space and parenthesis
        i += 4;
    }

    (*polynomial)->monomials = initMonomials(coefficients, degrees, n);
    if (NULL == (*polynomial)->monomials)
    {
        freePolynomial(polynomial);
        return EMEMORY;
    }
    (*polynomial)->degree = (*polynomial)->monomials[0].degree;
    return SUCCESS;
}

int     printPolynomial(const Polynomial *polynomial, char *file)
{

    assert(polynomial);

    int i;
    FILE *  out;

    if (file && (out = fopen(file, "w")) == NULL)
        return EOPEN;
    // If no file given, we use stdout
    if (NULL == file)
        out = stdout;
    fprintf(out, "(");
    if (NULL == polynomial->monomials)
        fprintf(out, "(0.0, 0)");
    for (i = 0; i < polynomial->n; i++)
    {
        printMonomial(polynomial->monomials[i], out);
        if (i < (polynomial->n - 1))
            fprintf(out, ", ");
    }
    fprintf(out, ")\n");
    if (out != stdout)
        fclose(out);
    return SUCCESS;
}
