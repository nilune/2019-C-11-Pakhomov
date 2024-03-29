/**
 * @file test_square.c
 * @author Pakhomov Mikhail
 * @brief Tests for square equation
 * @version 0.1
 * @date 2019-09-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "square.h"

#define EPSILON 1e-2
#define CHECK_EQUAL(a, b) ((((b)-EPSILON < (a)) && ((b) + EPSILON > (a))) ? True : False)
// #define PRINT_SQUARE(a, b, c, nRoots, x1, x2, test_nRoots, test_x1, text_x2) printf("")
#define PRINT_ERROR(err, test_nRoots, a, b, c, test_x1, test_x2)                              \
    {                                                                                         \
        printf("%s : assert_square() : test_count of roots=%d\n", err, test_nRoots);          \
        printf("a=%lf, b=%lf, c=%lf, test_x1=%lf, test_x2=%lf\n", a, b, c, test_x1, test_x2); \
    }

/**
 * @brief Assert func for solve_square_equation
 * 
 * Сalls the function of solving the quadratic equation and 
 * throws errors if the transmitted data do not coincide with the calculated ones
 * 
 * @param a First parameter
 * @param b Second parameter
 * @param c Third parameter
 * @param test_nRoots Expected count roots
 * @param test_x1 Expected first root
 * @param test_x2 Expected second root
 * @param flag Normal case or with complex numbers
 */
void assert_square(double a, double b, double c, int test_nRoots, double test_x1, double test_x2, int flag)
{
    double x1 = 0, x2 = 0;
    int nRoots = solve_square_equation(a, b, c, &x1, &x2, flag);
    if (nRoots != test_nRoots)
    {
        PRINT_ERROR("ERROR_NUMBER_ROOTS", test_nRoots, a, b, c, test_x1, test_x2);
        printf("count of roots=%d\n\n", nRoots);
        exit(EXIT_FAILURE);
    }

    if (nRoots == ONE_ROOT)
    {
        if (!CHECK_EQUAL(x1, test_x1))
        {
            PRINT_ERROR("ERROR_VALUE_ROOT", test_nRoots, a, b, c, test_x1, test_x2);
            printf("count of roots=%d, x1=%lf\n\n", nRoots, x1);
            // printf("ERROR_VALUE_ROOT : assert_square() : count of roots=1; \n"
            //        "a=%lf, b=%lf, c=%lf, test_x1=%lf, test_x2=%lf\n"
            //        "x1=%lf\n\n",
            //        a, b, c, test_x1, test_x2, x1);
            exit(EXIT_FAILURE);
        }
    }
    else if (nRoots == TWO_ROOTS || nRoots == COMPLEX_ROOTS)
    {
        if (!((CHECK_EQUAL(x1, test_x1) && CHECK_EQUAL(x2, test_x2)) ||
              (CHECK_EQUAL(x2, test_x1) && CHECK_EQUAL(x1, test_x2))))
        {
            PRINT_ERROR("ERROR_VALUE_ROOT", test_nRoots, a, b, c, test_x1, test_x2);
            printf("count of roots=%d, x1=%lf, x2=%lf\n\n", nRoots, x1, x2);
            // printf("ERROR_VALUE_ROOT : assert_square() : count of roots=2; \n"
            //        "a=%lf, b=%lf, c=%lf, test_x1=%lf, test_x2=%lf\n"
            //        "x1=%lf, x2=%lf\n\n",
            //        a, b, c, test_x1, test_x2, x1, x2);
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * @brief Test input of square  function
 */
void test_square_input()
{
    double x1 = 0, x2 = 0;
    solve_square_equation((int)5.64, 1, 4, &x1, &x2, False);
}

/**
 * @brief Test normal roots of square  function
 * 
 */
void test_square_ordinary_roots()
{
    assert_square(1, -5, 6, TWO_ROOTS, 3, 2, False);
    assert_square(2.3, 5.6, 3.01, TWO_ROOTS, -0.80, -1.63, False);

    int i = 0;
    double x1, x2;
    srand(time(NULL));
    for (i; i < 100000; i++)
    {
        x1 = (-10 + rand() % 10);
        x2 = (1 + rand() % 10);
        assert_square(1, -(x1 + x2), x1 * x2, TWO_ROOTS, x1, x2, False);
    }
}

/**
 * @brief Test complex square roots
 * 
 */
void test_square_complex_roots()
{
    assert_square(1, 2, 2, COMPLEX_ROOTS, -1, 1, True);
    assert_square(2.1, 1.34, 4.56, COMPLEX_ROOTS, -0.31, 1.43, True);
}

/**
 * @brief Test extreme cases of square function
 * 
 */
void test_square_extreme_cases_roots()
{
    assert_square(0, 0, 0, INFINITY_ROOTS, 0, 0, False); // 0 = 0
    assert_square(0, 0, 1, ZERO_ROOTS, 0, 0, False);     // 1 = 0
    assert_square(0, 1, 0, ONE_ROOT, 0, 0, False);       // x = 0
    assert_square(0, 1, 1, ONE_ROOT, -1, 0, False);      // x + 1 = 0
    assert_square(1, 0, 0, ONE_ROOT, 0, 0, False);       // x^2 = 0
    assert_square(1, 1, 0, TWO_ROOTS, 0, -1, False);     // x^2 + x = 0
    assert_square(1, 2, 1, ONE_ROOT, -1, 0, False);      // x^2 + 2 * x + 1 = 0
    assert_square(1, 1, 1, ZERO_ROOTS, 0, 0, False);     // x^2 + x + 1 = 0
}

/**
 * @brief All tests
 * 
 */
void test_square()
{
    // test_square_input();
    test_square_ordinary_roots();
    test_square_complex_roots();
    test_square_extreme_cases_roots();
}

/**
 * @brief Starts tests
 * 
 * @return int Program exit status
 */
int main()
{
    printf("---------------------------------------------------\n");
    printf("Tests of function - solving square equation started\n"
           "from file ./square.c and lib ./square.h\n\n");
    test_square();
    printf("Tests succesfully completed\n\n");
    printf("---------------------------------------------------\n");
    return 0;
}
