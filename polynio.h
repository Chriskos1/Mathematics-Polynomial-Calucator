#ifndef POLYNIO_H_INCLUDED
#define POLYNIO_H_INCLUDED

enum POLYNIO_ERRORS
{
    SUCCESS = 0,
    ENOTFOUND = 1, // File not found or empty
    EWFORMAT = 2, // Wrong input format
    EOPEN = 3, // Error on opening for writing
    EMATH = 4, // Invalid polynomial
    EMEMORY = 5 // Problem while allocated with malloc
};

/** FUNCTIONS THAT READ OR WRITE */

/**
NAME: cleanStdin - clean stdin
SYNOPSIS: clean stdin after scanf (avoid problem if input is wrong)
PARAMETERS: none
RETURN: none
*/
void cleanStdin();

/**
NAME: readPolynomial - allocate/initialize a polynomial by parameters
SYNOPSIS: Allocate, initialize a new polynomial set to the values given by parameters
PARAMETERS:
    - Polynomial **polynomial: newly allocated polynomial; NULL if an error status is returned
    - const double *coefficients: an array with all coefficients
    - const int *degrees: an array with all degrees (order must match with coefficients array)
    - const int n: number of monomials
RETURN: status code (cf. POLYNIO_ERRORS)
*/
int     readPolynomial(Polynomial **polynomial, const double *coefficients, const int *degrees, const int n);


/**
NAME: readPolynomialStdin - allocate/initialize a polynomial by user
SYNOPSIS: Allocate, initialize and return a new polynomial set to the values given by stdin
PARAMETERS:
    - Polynomial **polynomial: newly allocated polynomial; NULL if an error status is returned
RETURN: status code (cf. POLYNIO_ERRORS)
*/
int         readPolynomialStdin(Polynomial **polynomial);

/**
NAME: readPolynomialFile - allocate/initialize a polynomial by file
SYNOPSIS: Allocate, initialize and return a new polynomial set to the values given from a file
PARAMETERS:
    - Polynomial **polynomial: newly allocated polynomial; NULL if an error status is returned
    - const char *file: name of the file to read
NOTES:
    File format: ((coeff1, degree1), (coeff2, degree2), (coeff3, degree3), [...])
RETURN: status code (cf. POLYNIO_ERRORS)
*/
int         readPolynomialFile(Polynomial **polynomial, const char *file);

/**
NAME: printPolynomial - display a polynomial
SYNOPSIS: Display the given polynomial to stdin or on a file
PARAMETERS:
    - Polynomial *polynomial: the polynomial to display
    - char *file: name of the file to use
NOTES:
    Format: ((coeff1, degree1), (coeff2, degree2), (coeff3, degree3), [...])
    If file is not NULL, write the given polynomial on it instead of displaying it to stdin
    If the file doesn't exist, create it
RETURN: status code (cf. POLYNIO_ERRORS)
*/
int        printPolynomial(const Polynomial *polynomial, char *file);

#endif // POLYNIO_H_INCLUDED
