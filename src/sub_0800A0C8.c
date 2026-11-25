extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u16 D_02021E90[];
extern s32 D_08671BB0[];

/* Copy a value from the parent object into this script actor, refresh the
 * display state, then dispatch and advance to the next script step. */
void sub_0800A0C8(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *source = *(u8 **)(self + 0x3C);
    u8 *valuePtr = source + 0x635;
    u8 *entry;
    u8 zero = 0;
    u8 value;
    s32 *lit;
    value = *valuePtr;
    *(u8 *)(self + 0x4C) = value;
    D_02021E90[0x950] &= 0xDFFF;
    D_02021E90[0x951] = ((*valuePtr + 1) << 8) | 9;
    *(u8 *)(source + 0x637) = zero;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    lit = (s32 *)0x08671BB0;
    entry = self + 0x18;
    sub_080C31E4(entry, self + 0x22, *lit);
    (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19))++;
    entry += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(s32 *)((u8 *)*(void **)(self + 0x14) + *entry * 4));
}
