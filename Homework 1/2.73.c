#include <limits.h>

/* Addition that saturates to TMin or TMax */
int saturating_add (int x, int y) {
    /* Determine num of bytes and answer even if
	it overflowed */
    int byteSize = sizeof(int)<<3;
    int result = x + y;

    /* Determine signs of products and result */
    int signOfX = (x>>(byteSize - 1)) & 0x01;
    int signOfY = (y>>(byteSize - 1)) & 0x01;
    int signOfResult = (result>>(byteSize - 1)) & 0x01;

    /* Determine whether an overflow happened */
    int isOverflowPossible = ~(signOfX ^ signOfY);
    int didOverflow = (signOfX ^ signOfResult) & isOverflowPossible;

    /* Return result if no overflow happened, or if it
    did return INT_MAX or INT_MIN */
    int extendOverflow = ~didOverflow + 1;
    int extendedXSign = ~signOfX + 1;                           
    int overflow = INT_MAX ^ extendedXSign;
    overflow = extendOverflow & overflow;
    result = (~ extendOverflow) & result;

    return overflow | result;
}