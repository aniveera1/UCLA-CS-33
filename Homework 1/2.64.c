/* Return 1 when any odd bit of x equals 1; 0 otherwise
	Assume w=32 */
int any_odd_one (unsigned x) {
    /* The hexdecimal 0x55555555 is 32 bits long
     and has a 1 at every odd bit and a 0 at every 
     even bit */
	return (x & 0x55555555) != 0x00000000;
}