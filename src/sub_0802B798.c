void setAnimationFrame(void *, void *, s32, s32);
s32 rollProbability(s32);
s32 sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, s32, s32);

/* Set an entity's pose, then temporarily advance its state slot to fetch and dispatch
 * a handler from the table at 0x0866DB0C, restoring the slot afterwards; when the
 * pose's flag is set, apply a random up/down velocity and end the state. */
void sub_0802B798(void *self) {
    void *gfx;
    void *work;
    u8 *anim;
    u8 *stateByte;
    u8 handlerIdx;
    u32 handlerTable;
    gfx = *(void **)((u8 *)self + 0x38);
    work = *(void **)((u8 *)self + 0x3C);
    anim = (u8 *)work + 0x34;
    setAnimationFrame(gfx, anim, 0x5, 0);
    *(u32 *)((u8 *)work + 0x10) = 0;
    *(u32 *)((u8 *)self + 0x14) = 0x0866DB0C;
    *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) + 1;
    {
        u8 *stateEntry;
        stateEntry = (u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
        *(u8 *)(stateEntry + 0x19) = *(u8 *)(stateEntry + 0x19) + 1;
    }
    {
        s32 stateOffset;
        stateOffset = (s32)(s16)(*(s16 *)((u8 *)self + 0x22)) * 2;
        stateByte = (u8 *)self;
        stateByte += 0x18;
        stateByte += stateOffset;
        handlerIdx = *stateByte;
    }
    handlerTable = *(u32 *)((u8 *)self + 0x14);
    sub_080C31E0((s32)self, *(u32 *)((u32)(handlerIdx * 4) + handlerTable));
    *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) - 1;
    if (2 & *(u8 *)anim) {
        u32 *handlerSlot;
        u8 *stateEntry;
        s32 velocity;
        velocity = rollProbability(0x1388);
        if (velocity == 1)
            velocity = 0x8000;
        else
            velocity = 0xFFFF8000;
        *(u32 *)((u8 *)work + 0x10) = velocity;
        stateEntry = (u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
        {
            u8 cleared;
            cleared = 0;
            *(u8 *)(stateEntry + 0x19) = cleared;
        }
        handlerSlot = (u32 *)0x08671BD0;
        sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 0, *handlerSlot);
    }
}
