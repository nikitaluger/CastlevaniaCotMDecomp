extern void sub_080C31E4(void *, void *, s32);
extern s32 sub_08014A04(void *, s32, s32, s32, s32);
extern void sub_08014B1C(void *, void *, s32, s32);
extern s32 gMainObjTimerCallbacks[];

void sub_08026780(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *r4 = *(u8 **)(self + 0x3C);
    u8 *r6 = r4 + 0xA8;
    s32 *lit;

    if (sub_08014A04(r6, *(s32 *)(r4 + 8), *(s32 *)(r4 + 0xC), 0xC0000, 0xC0000) == 1) {
        s16 idx = *(s16 *)(self + 0x22);
        *(u8 *)(self + idx * 2 + 0x19) = 0;
        lit = gMainObjTimerCallbacks;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
        return;
    }
    sub_08014B1C(r6, r4 + 0xDC, *(s32 *)(r4 + 8), *(s32 *)(r4 + 0xC));
}

void sub_0802697C(void *arg0) {
    u32 *base = *(u32 **)((u8 *)arg0 + 0x3C);
    u32 *p = base + 0x1A;
    s32 i = 4;
    u32 zero = 0;
    u32 one = 1;
    do {
        u32 q = *p;
        if (q != 0) {
            *(u16 *)(q + 0x64) |= (u16)one;
            *p = zero;
        }
        p++;
        i--;
    } while (i >= 0);
}

/* Set flag bits `bits` in the +0x64 halfword of each of the 5 slot objects,
 * skipping empty slots. */
void sub_080269A8(void *entity, u16 bits) {
    u32 *slots = *(u32 **)((u8 *)entity + 0x3C);
    u32 *p = slots + 0x1A;
    s32 i = 4;
    do {
        u32 member = *p;
        if (member != 0) {
            *(u16 *)(member + 0x64) |= bits;
        }
        p++;
        i--;
    } while (i >= 0);
}
