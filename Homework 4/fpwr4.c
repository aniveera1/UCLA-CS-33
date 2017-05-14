static float u2f(unsigned u)
{
    /* Use union to preserve exact bit representation */
    union container {
        unsigned previous;
        float value;
    };
    
    union container temp;
    temp.previous = u;
    return temp.value;
}

float fpwr4(int x)
{
    /* Result exponent and fraction */
    unsigned exp, frac;
    unsigned u;
    
    if (x < -74) {
        /* Too small. Return 0.0 */
        exp = 0;
        frac = 0;
    } else if (x < -63) {
        /* Denormalized result */
        exp = 0;
        frac = 0x00200003 >> ((64 - x) - 128) * 2;
    } else if (x < 64) {
        /* Normalized result */
        exp = (2 * x) + 127;
        frac = 0;
    } else {
        /* Too big. Return +oo */
        exp = 255;
        frac = 0;
    }
    
    /* Pack exp and frac into 32 bits */
    u = exp << 23 | frac;
    /* Return as float */
    return u2f(u);
}
