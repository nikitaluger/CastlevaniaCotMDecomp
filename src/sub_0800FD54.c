extern s32 sub_080C2F20(s32, s32);
extern s32 sub_080C2F24(s32, s32);

/* Write the decimal digits of `value`, least significant first, into successive
 * s16 slots starting at `digits` and moving backwards; `charBase` is added to
 * each digit (the font's '0' code point). */
void sub_0800FD54(s32 value, s32 charBase, s16 *digits) {
    s32 v = value;
    s16 *p = digits;
    s32 base = (u16)charBase;
    s32 digit;
    do {
        digit = sub_080C2F24(v, 10);
        v = sub_080C2F20(v, 10);
        *p = base + digit;
        p--;
    } while (v != 0);
}
