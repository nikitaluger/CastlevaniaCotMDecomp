void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
struct WorkState { u8 pad[0xEC]; u16 flipFlags; };

/* Resets the work state's phase, flip flag and motion fields, then runs the
 * next script step and switches to the following AI handler. */
void sub_080A62E4(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *cursor = *(u8 **)(self + 0x3C);

    {
        u32 zero;
        u32 clearOff;
        u8 *phase = cursor + 0xEE;
        zero = 0;
        *phase = zero;
        *(u8 *)(cursor + 0xEF) = 2;
        ((struct WorkState *)cursor)->flipFlags = 0x10 & *(u16 *)(sprite + 2);
        *(u32 *)(cursor + 0x114) = 0x60;
        clearOff = zero + 0x128;
        *(u32 *)(cursor + clearOff) = zero;
        *(u32 *)(cursor + clearOff + 4) = zero;
        *(u32 *)(cursor + clearOff + 0xC) = zero;
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        s32 *scriptTable = (s32 *)0x08671BB0;
        cursor = self + 0x18;
        sub_080C31E4(cursor, self + 0x22, *scriptTable);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        cursor += *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(self, *(s32 *)(*(u32 *)(self + 0x14) + *(u8 *)cursor * 4));
    }
}
