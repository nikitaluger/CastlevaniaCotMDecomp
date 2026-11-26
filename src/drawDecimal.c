extern s32 divideInt(s32, s32);
extern s32 moduloInt(s32, s32);

/* Write the decimal digits of `value`, least significant first, into successive
 * s16 slots starting at `digits` and moving backwards; `charBase` is added to
 * each digit (the font's '0' code point). */
void drawDecimal(s32 value, s32 charBase, s16 *digits) {
    s32 v = value;
    s16 *p = digits;
    s32 base = (u16)charBase;
    s32 digit;
    do {
        digit = moduloInt(v, 10);
        v = divideInt(v, 10);
        *p = base + digit;
        p--;
    } while (v != 0);
}
