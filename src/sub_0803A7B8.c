void sub_080144D8(void *, void *);
void sub_080144FC(void *, void *);
void sub_080C31E0(void *, void *);

/* Enter the entity's handler state: reset its sub-state, install the handler
 * table at 0x0866DF48, call the handler up one state (and back), then refresh
 * the sprite's screen position when it is flagged visible. */
void sub_0803A7B8(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    s32 stateOffset;
    u8 *stateSlot;
    u8 handlerIndex;
    sub_080144D8(arg0, sprite);
    *(u32 *)(self + 0x14) = 0x0866DF48;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    stateOffset = *(s16 *)(self + 0x22) * 2;
    *(u8 *)((u32)stateOffset + (u32)self + 0x19) = *(u8 *)((u32)stateOffset + (u32)self + 0x19) + 1;
    stateOffset = *(s16 *)(self + 0x22) * 2;
    stateSlot = self;
    stateSlot += 0x18;
    stateSlot += stateOffset;
    handlerIndex = *(u8 *)stateSlot;
    sub_080C31E0(arg0, *(void **)(handlerIndex * 4 + *(u32 *)(self + 0x14)));
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    {
        u8 *flag = sprite;
        flag += 0x2A;
        if (0x40 & *(u8 *)flag) sub_080144FC(arg0, sprite);
    }
}
