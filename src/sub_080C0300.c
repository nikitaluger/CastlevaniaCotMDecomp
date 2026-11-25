extern u8 D_0810C7C8[];    /* packed nibble LUT: high nibble = shift, low nibble = entry */
extern u32 D_0810C87C[];   /* fixed-point envelope amplitude values */
s32 sub_080BF7B8(s32 a, s32 b);   /* fixed-point multiply helper */

/* Evaluates the curve object's envelope at position arg1 (clamped to 0xB2)
 * and fraction arg2, interpolating between the two neighbouring amplitude
 * entries, then scales the result by the object's +4 multiplier. */
s32 sub_080C0300(void *arg0, u32 arg1, u32 arg2)
{
    u8 index;
    s32 fraction;
    u32 value0;
    u8 nextEntry;
    u32 value1;
    s32 scale;

    index = arg1;
    fraction = (s32)(arg2 << 24);
    if (index > 0xB2)
    {
        index = 0xB2;
        fraction = 0xFF000000;
    }

    value0 = D_0810C7C8[index];
    value0 = D_0810C87C[value0 & 0xF] >> (value0 >> 4);

    nextEntry = D_0810C7C8[index + 1];
    value1 = D_0810C87C[nextEntry & 0xF] >> (nextEntry >> 4);

    scale = *(s32 *)((u8 *)arg0 + 4);
    return sub_080BF7B8(scale, (s32)value0 + sub_080BF7B8((s32)value1 - (s32)value0, fraction));
}
