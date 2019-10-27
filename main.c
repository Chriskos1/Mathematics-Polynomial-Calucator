#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include "monomial.h"
#include "polynstruct.h"
#include "polynmath.h"
#include "polynio.h"
#include "polynomials.h"

static void    printMenu()
{
    printf("MENU\n");
    printf("1) Manage polynomials list\n");
    printf("2) Mathematical operations on polynomials\n");
    printf("3) Exit\n\n");
    printf("Choice: ");
}

static void    printMenuMathematicalOperations()
{
    printf("MATHEMATICAL OPERATIONS ON POLYNOMIALS\n");
    printf("1) Value of a polynomial for an x given\n");
    printf("2) Value of a polynomial for an x given (Horner method)\n");
    printf("3) Derivative of a polynomial\n");
    printf("4) Primitive of a polynomial\n");
    printf("5) N-th power of a polynomial\n");
    printf("6) Sum of two polynomials\n");
    printf("7) Multiplication of two polynomials\n");
    printf("8) Derivative of the sum of two polynomials\n");
    printf("9) Derivative of the multiplication of two polynomials\n");
    printf("0) Return to the menu\n\n");
    printf("Choice: ");
}

static void    printMenuManagePolynomial()
{
    printf("MANAGE POLYNOMIALS LIST\n");
    printf("1) Print polynomials\n");
    printf("2) Add a polynomial\n");
    printf("3) Remove a polynomial\n");
    printf("4) Remove all polynomials from the list\n");
    printf("5) Print polynomial on a file\n");
    printf("0) Return to the menu\n\n");
    printf("Choice: ");
}

static void   menuMathematicalOperations(Polynomials *polynomials)
{
    int choice;
    Polynomial *polynomial1 = NULL;
    Polynomial *polynomial2 = NULL;
    Polynomial *polynomialResult = NULL;
    int x;
    int target;
    float result;
    do
    {
        printMenuMathematicalOperations();
        scanf("%d", &choice);
        cleanStdin();
        while (choice < 0 || choice > 9)
        {
            printf("Invalid choice\nChoice: ");
            scanf("%d", &choice);
            cleanStdin();
        }
        if (choice == 0)
            continue;
        printf("CHOOSE THE POLYNOMIAL\n");
        printPolynomials(polynomials);
        printf("Choose the polynomial: ");
        scanf("%d", &target);
        cleanStdin();
        while (target < 1 || target > polynomials->cardinal)
        {
            printf("Invalid polynomial\nPolynomial (number): ");
            scanf("%d", &target);
            cleanStdin();
        }
        polynomial1 = polynomials->polynomialslList[target - 1];
        printf("\n");
        if (choice > 5)
        {
            printf("CHOOSE THE SECOND POLYNOMIAL\n");
            printPolynomials(polynomials);
            printf("Choose the second polynomial: ");
            scanf("%d", &target);
            cleanStdin();
            while (target < 1 || target > polynomials->cardinal)
            {
                printf("Invalid polynomial\nPolynomial (number): ");
                scanf("%d", &target);
                cleanStdin();
            }
            polynomial2 = polynomials->polynomialslList[target - 1];
            printf("\n");
        }
        switch(choice)
        {
        case 1:
        {
            printf("SOLVE POLYNOMIAL\n");
            printf("Choose the x value: ");
            scanf("%d", &x);
            cleanStdin();
            result = polynSolve(polynomial1, x);
            printPolynomial(polynomial1, NULL);
            printf("\nResult of this polynomial solved by %d = %.2f\n",  x, result);
            break;
        }
        case 2:
        {
            printf("SOLVE POLYNOMIAL BY HORNER METHOD\n");
            printf("Choose the x value: ");
            scanf("%d", &x);
            cleanStdin();
            result = polynSolveHorner(polynomial1, x);
            printPolynomial(polynomial1, NULL);
            printf("\nResult of this polynomial solved by %d = %.2f\n",  x, result);
            break;
        }
        case 3:
        {
            printf("DERIVATIVE OF A POLYNOMIAL\n");
            polynomialResult = polynDeriv(polynomial1);
            if (NULL == polynomialResult)
            {
                printf("An error occur while deriving the polynomial\n");
                printf("A malloc error occurs\nOr your polynomial has a zero degree\n");
            }
            else
            {
                printf("Polynomial given: \n");
                printPolynomial(polynomial1, NULL);
                printf("Derivative of the polynomial: \n");
                printPolynomial(polynomialResult, NULL);
            }
            break;
        }
        case 4:
        {
            printf("PRIMITIVE OF A POLYNOMIAL\n");
            polynomialResult = polynPrimitive(polynomial1);
            if (NULL == polynomialResult)
            {
                printf("An error occur while doing the primitive of the polynomial\n");
                printf("It should be a problem with allocation\n");
                printf("The primitive of the coefficient of a monomial is maybe under 0.01 (it's a protective limit)\n");
            }
            else
            {
                printf("Polynomial given: \n");
                printPolynomial(polynomial1, NULL);
                printf("Primitive of the polynomial: \n");
                printPolynomial(polynomialResult, NULL);
            }
            break;
        }
        case 5:
        {
            printf("N-th POWER OF A POLYNOMIAL\n");
            printf("Choose the n value: ");
            scanf("%d", &x);
            cleanStdin();
            while (x < 0 && x > 30)
            {
                printf("Invalid n\nn: ");
                scanf("%d", &x);
                cleanStdin();
            }
            polynomialResult = polynNPow(polynomial1, x);
            if (NULL == polynomialResult)
            {
                printf("An error occur while doing the N-th power of the polynomial\n");
            }
            else
            {
                printf("Polynomial given: \n");
                printPolynomial(polynomial1, NULL);
                printf("N-th power of the polynomial: \n");
                printPolynomial(polynomialResult, NULL);
            }
            break;
        }
        case 6:
        {
            printf("SUM OF TWO POLYNOMIALS\n");
            polynomialResult = polynSum(polynomial1, polynomial2);
            if (NULL == polynomialResult)
            {
                printf("An error occur while doing the sum of the two polynomial\n");
            }
            else
            {
                printf("Polynomials given: \n");
                printPolynomial(polynomial1, NULL);
                printPolynomial(polynomial2, NULL);
                printf("Sum of those polynomials: \n");
                printPolynomial(polynomialResult, NULL);
            }
            break;
        }
        case 7:
        {
            printf("MULTIPLICATION OF TWO POLYNOMIALS\n");
            polynomialResult = polynMult(polynomial1, polynomial2);
            if (NULL == polynomialResult)
            {
                printf("An error occur while doing the multiplication of the two polynomial\n");
            }
            else
            {
                printf("Polynomials given: \n");
                printPolynomial(polynomial1, NULL);
                printPolynomial(polynomial2, NULL);
                printf("Multiplication of those polynomials: \n");
                printPolynomial(polynomialResult, NULL);
            }
            break;
        }
        case 8:
        {
            printf("DERIVATIVE OF THE SUM OF TWO POLYNOMIALS\n");
            printPolynomial(polynomial1, NULL);
            printPolynomial(polynomial2, NULL);
            polynomialResult = polynDerivSum(polynomial1, polynomial2);
            if (NULL == polynomialResult)
            {
                printf("An error occur while doing the derivative of the sum of the two polynomial\n");
                printf("A malloc error occurs\nOr a polynomial has a zero degree\n");
            }
            else
            {
                printf("Polynomials given: \n");
                printPolynomial(polynomial1, NULL);
                printPolynomial(polynomial2, NULL);
                printf("Derivative of the sum of those polynomials: \n");
                printPolynomial(polynomialResult, NULL);
            }
            break;
        }
        case 9:
        {
            printf("DERIVATIVE OF THE MULTIPLICATION OF TWO POLYNOMIALS\n");
            polynomialResult = polynDerivMult(polynomial1, polynomial2);
            if (NULL == polynomialResult)
            {
                printf("An error occur while doing the derivative of the multiplication of the two polynomial\n");
                printf("A malloc error occurs\nOr a polynomial has a zero degree\n");
            }
            else
            {
                printf("Polynomials given: \n");
                printPolynomial(polynomial1, NULL);
                printPolynomial(polynomial2, NULL);
                printf("Derivative of the multiplication of those polynomials: \n");
                printPolynomial(polynomialResult, NULL);
            }
            break;
        }
        default:
        {
            break;
        }
        }
        int res;
        printf("\n");
        if (choice >= 3 && choice <= 9 && NULL != polynomialResult)
        {
            res = addPolynomial(polynomials, polynomialResult);
            if (SUCCESS == res)
                printf("The polynomial was successfully added to the list\n\n");
            else
            {
                printf("Error while trying to add the polynomial to the list\n\n");
            }
        }
    }
    while (choice != 0);
    printf("Returning to the menu\n");
}

static void   menuManagePolynomial(Polynomials *polynomials)
{
    int choice;
    int ret;
    int target;
    char buff[200];
    Polynomial *newPolynomial = NULL;
    do
    {
        printMenuManagePolynomial();
        scanf("%d", &choice);
        cleanStdin();
        while (choice < 0 || choice > 5)
        {
            printf("Invalid choice\nChoice: ");
            scanf("%d", &choice);
            cleanStdin();
        }
        switch(choice)
        {
        case 1:
        {
            printf("LIST OF POLYNOMIALS\n");
            printPolynomials(polynomials);
            break;
        }
        case 2:
        {
            printf("ADD A POLYNOMIAL\n");
            printf("1) From the console\n2) From a file\n\nchoice: ");
            scanf("%d", &target);
            cleanStdin();
            while (target < 1 && target > 2)
            {
                printf("Invalid choice\nChoice: ");
                scanf("%d", &target);
                cleanStdin();
            }
            printf("\n");
            if (1 == target)
                ret = readPolynomialStdin(&newPolynomial);
            else
            {
                printf("Which file to use (format: file.txt): ");
                scanf("%s", buff);
                cleanStdin();
                ret = readPolynomialFile(&newPolynomial, buff);
            }
            if (EMEMORY == ret)
                fprintf(stderr, "Malloc error\n");
            else if (EOPEN == ret)
                fprintf(stderr, "Could not open the file\n");
            else if(EWFORMAT == ret || EMATH == ret)
                fprintf(stderr, "Wrong format or mathematical error\n");
            else
            {
                ret = addPolynomial(polynomials, newPolynomial);
                if (SUCCESS == ret)
                {
                    printPolynomial(newPolynomial, NULL);
                    printf("Polynomial was added to the list\n");
                }
                else
                    printf("Memory problem while adding the polynomial to the list\n");
            }
            break;
        }
        case 3:
        {
            printf("REMOVE A POLYNOMIAL\n");
            if (polynomials->cardinal == 0)
            {
                printf("List of polynomial is empty");
                break;
            }
            printf("List of polynomials\n");
            printPolynomials(polynomials);
            printf("Which polynomial do we have to remove? ");
            scanf("%d", &target);
            cleanStdin();
            while (target < 1 || target > polynomials->n)
            {
                printf("Invalid polynomial\nPolynomial (number): ");
                scanf("%d", &target);
                cleanStdin();
            }
            freeOnePolynomial(polynomials, target);
            printf("The polynomial was removed\n");
            break;

        }
        case 4:
        {
            printf("REMOVE ALL POLYNOMIALS\n");
            freePolynomials(polynomials);
            printf("All polynomials were removed\n");
            break;
        }
        case 5:
        {
            printf("PRINT POLYNOMIAL ON A FILE\n");
            if (polynomials->cardinal == 0)
            {
                printf("List of polynomial is empty");
                break;
            }
            printf("List of polynomials\n");
            printPolynomials(polynomials);
            printf("Which polynomial do we have to print? ");
            scanf("%d", &target);
            cleanStdin();
            while (target < 1 || target > polynomials->n)
            {
                printf("Invalid polynomial\nPolynomial (number): ");
                scanf("%d", &target);
                cleanStdin();
            }
            printf("Which file to use (format: file.txt): ");
            scanf("%s", buff);
            cleanStdin();
            ret = printPolynomial(polynomials->polynomialslList[target - 1], buff);
            if (EOPEN == ret)
            {
                printf("Error: could not open the file\n\n");
            }
            else
                printf("Polynomial was successfully printed on the file\n\n");
            break;
        }
        default:
        {
            break;
        }
        }
        printf("\n\n");
    }
    while (choice != 0);
    printf("Returning to the menu\n");
}

int main()
{
    printf("WELCOME TO THE POLYNOMIAL PROJECT\n\n");

    Polynomials     polynomials;
    Polynomial **pList = NULL;
    pList = malloc(10 * sizeof(Polynomial *));
    if (NULL == pList)
    {
        fprintf(stderr, "Malloc error while creating the array of polynomials.\nQuit\n");
        exit(EXIT_FAILURE);
    }
    polynomials.polynomialslList = pList;
    polynomials.cardinal = 0;
    polynomials.n = 10;

    printf("CREATION OF A DEFAULT POLYNOMIAL\n");
    Polynomial *pDefault = NULL;

    int degrees[6] = {8, 5, 6, 8, 4, 3};
    double coefficients[6] = {5, 6, 1, 12, 5, 1};

    pDefault = initPolynomial();
    if (NULL == pDefault)
    {
        fprintf(stderr, "Malloc error\nQuit");
        free(pList);
        exit(EXIT_FAILURE);
    }
    printf("A default polynomial was successfully allocated and initialized to the nul polynomial\n");
    printPolynomial(pDefault, NULL);

    int res;
    res = readPolynomial(&pDefault, coefficients, degrees, 6);
    if (res == EMEMORY)
    {
        fprintf(stderr, "Malloc error\nQuit");
        freePolynomial(&pDefault);
        free(pList);
        exit(EXIT_FAILURE);
    }
    printf("CREATED A NEW POLYNOMIAL WITH DEFAULT SETTINGS\n");
    printPolynomial(pDefault, NULL);
    reductOrderPolynomial(pDefault);
    printf("Polynomial ordered and reduced\n");
    printPolynomial(pDefault, NULL);
    printf("\n\n");
    polynomials.polynomialslList[polynomials.cardinal] = pDefault;
    polynomials.cardinal += 1;

    int choice;
    do
    {
        printMenu();
        scanf("%d", &choice);
        cleanStdin();
        while (choice < 1 || choice > 3)
        {
            printf("Invalid choice\n");
            printf("Choice: ");
            scanf("%d", &choice);
            cleanStdin();
        }
        switch(choice)
        {
        case 1:
        {
            menuManagePolynomial(&polynomials);
            break;
        }
        case 2:
        {
            if (polynomials.cardinal == 0)
            {
                printf("List of polynomial is empty, can't use mathematical functions without polynomial in the list\n\n");
                break;
            }
            menuMathematicalOperations(&polynomials);
            break;
        }
        default:
            break;
        }
    }
    while (choice != 3);

    freePolynomials(&polynomials);
    free(polynomials.polynomialslList);
    polynomials.polynomialslList = NULL;
    printf("See you later!\n");

    return 0;
}
