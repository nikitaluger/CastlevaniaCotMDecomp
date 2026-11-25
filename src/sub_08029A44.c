extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 D_08671BD8[];

/* When the actor's object has flag bit 2 set, clears the current script action
 * byte and dispatches handler 0 from table D_08671BD8. */
void sub_08029A44(void *self) {
    if (4 & *(u16 *)((u8 *)*(void **)((u8 *)self + 0x3C) + 2)) {
        s16 slot = *(s16 *)((u8 *)self + 0x22);
        s32 *handlerTable;
        *(u8 *)((u8 *)self + slot * 2 + 0x17) = 0;
        handlerTable = D_08671BD8;
        sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 0, *handlerTable);
    }
}
