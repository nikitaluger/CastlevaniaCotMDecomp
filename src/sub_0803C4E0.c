s32 sub_080141AC(void *, void *);
void sub_080C31E0(void *, void *);
void sub_08013C8C(void *, void *);

/* Advance the entity to its next handler state, run that handler, then update its
 * screen position; if the entity has just come into view, run the handler in
 * slot 0x24 instead. */
void sub_0803C4E0(void *arg0) {
    u8 *self = arg0;
    void *sprite = *(void **)(self + 0x38);
    if (sub_080141AC(sprite, *(void **)(self + 0x3C)) == 1) {
        sub_080C31E0(arg0, *(void **)(self + 0x24));
        return;
    }
    *(u32 *)(self + 0x14) = 0x0866DFA8;
    *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) + 1);
    {
        u8 *stateEntry = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        stateEntry[0x19] = (u8)(stateEntry[0x19] + 1);
        {
            s32 stateOffset = (*(s16 *)(self + 0x22)) * 2;
            u8 *stateBase = self + 0x18;
            u8 handlerIndex = *(stateBase + stateOffset);
            void **handlerTable = *(void **)(self + 0x14);
            void *handler = handlerTable[handlerIndex];
            sub_080C31E0(arg0, handler);
        }
    }
    *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) - 1);
    sub_08013C8C(arg0, sprite);
}
