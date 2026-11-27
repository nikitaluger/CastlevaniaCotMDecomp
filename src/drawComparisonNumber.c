extern unsigned char D_080CAFCC[]; /* palette per comparison result */
void sub_0800FE64(unsigned int a, unsigned char b, int c, int d, int e);

/* Draw a 4-digit number at tilemap 0x511C, using a palette picked by comparing
 * value with limit (below: 0x07, equal: 0x05, above: 0x06); returns -1/0/1 for
 * the comparison. */
int drawComparisonNumber(unsigned int value, unsigned int limit, int dest)
{
    int comparison;
    int paletteIndex;
    if (value > limit) {
        paletteIndex = 2;
        comparison = 1;
    } else if (value == limit) {
        paletteIndex = 1;
        comparison = 0;
    } else {
        paletteIndex = 0;
        comparison = -1;
    }
    sub_0800FE64(value, D_080CAFCC[paletteIndex], 4, 0x511C, dest);
    return comparison;
}

void sub_0800F370(unsigned char arg0) { }
void sub_0800F3C8(unsigned char arg0, int arg1) { }
void sub_0804BB7C(void *arg0, void *arg1) { }
