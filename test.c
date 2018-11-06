#include "test.h"
#include "algo.h"
#include "nrutil.h"

#include <stdlib.h>

void test_sigma_delta ()
{
    uint8_t I[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    uint8_t M_1[3][3] = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
    uint8_t M[3][3];
    sigma_delta(I, M, M_1, NULL, NULL, NULL, NULL, 3, 3);

    display_ui8matrix(I, 0, 3, 0, 3, "%ld", "TEST M");
}