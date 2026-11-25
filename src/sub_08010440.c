extern u8 D_02025358[];
extern u8 D_080CB230[];
void sub_08010250(void);
void sub_0801026C(void);

/* Load the save buffer, map its stage index at +0x9C through the D_080CB230
 * table to a bit in the +0xB progress mask, set that bit and return it; if it
 * was already set, return 0. Save the buffer back either way. */
s32 sub_08010440(void)
{
    s32 bit = 0;
    u8 *buf = D_02025358;

    sub_08010250();

    {
        s16 *pIdx = (s16 *)(buf + 0x9C);
        s32 idx = *pIdx;
        if (idx > 4) goto done;
        if (idx < 0) goto done;

        bit = D_080CB230[idx];
        if ((buf[0xB] >> bit) & 1) {
            bit = 0;
        } else {
            buf[0xB] = buf[0xB] | (1 << bit);
        }
    }

done:
    sub_0801026C();
    return bit;
}
