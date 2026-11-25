extern void sub_080C25B8(void *, void *);
extern void sub_080C2634(void *, void *, void *);
extern void sub_080C2500(void);

/* Add two floats: unpack both operands into 16-byte parts, add the parts, then
 * pack the result (the add routine leaves the result pointer in r0). */
void sub_080C27B0(s32 floatA, s32 floatB) {
    u8 partsA[0x10], partsB[0x10], result[0x10];
    s32 a = floatA, b = floatB;
    sub_080C25B8(&a, partsA);
    sub_080C25B8(&b, partsB);
    sub_080C2634(partsA, partsB, result);
    sub_080C2500();
}
