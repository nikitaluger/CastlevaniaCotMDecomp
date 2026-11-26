extern s32 sub_080C364C(s32, s32);
extern u8 gMainWorkspace[];
extern u8 D_080E0558[];

/* Screen-transition start: when the transition request flag (+0x14ED) is set,
 * clear it together with the two counters, enable the transition, compute the
 * step 0x100 / (size word at D_080E0558+0x5C) and store it at +0x1840. */
void sub_0806DD94(void) {
    u8 *state = gMainWorkspace;
    u32 zero;
    if (*(u8*)(state + 0x14ED)) {
        zero = 0;
        *(u8*)(state + 0x14ED) = zero;
        *(u32*)(state + 0x1818) = zero;
        *(u32*)(state + 0x181C) = zero;
        *(u32*)(state + 0x1834) = 1;
        {
            u8 *p1840 = state + 0x1840;
            u8 *scene = D_080E0558;
            s32 divisor = *(u32*)(scene + 0x5C);
            s32 dividend = 0x100;
            *(u32*)p1840 = sub_080C364C(dividend, divisor);
        }
        *(u32*)(state + 0x183C) = zero;
    }
}
