#include <limits.h>

/* Addition that saturates to TMin or TMax */
int saturating_add (int x, int y) {
    /* Determine num of bytes */
    int byteSize = sizeof(int)<<3;
    int result;

    /* Determine signs of product */
    int signOfX = (x>>(byteSize - 1)) & 0x01;

    /* Determine whether an overflow happened */
    int didOverflow = __builtin_add_overflow(x, y, &result);

    /* Return result if no overflow happened, or if it
    did return INT_MAX or INT_MIN */
    int extendOverflow = ~didOverflow + 1;
    int extendedXSign = ~signOfX + 1;                           
    int overflow = INT_MAX ^ extendedXSign;
    overflow = extendOverflow & overflow;
    result = (~ extendOverflow) & result;

    return overflow | result;
}