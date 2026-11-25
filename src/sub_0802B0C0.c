extern void sub_08011368(void *, void *, s32, s32);
extern s32 sub_08014EF4(s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Play pose 5 and stand still; when the pose finishes, launch the entity up or
 * down (which way is picked by the timer), clear its state slot and detach it. */
void sub_0802B0C0(void *self)
{
    u8 *work;
    void *gfx;
    u8 *anim;

    gfx = *(void **)((u8 *)self + 0x38);
    work = *(u8 **)((u8 *)self + 0x3C);
    anim = work + 0x34;

    *(s32 *)(work + 0x10) = 0;
    sub_08011368(gfx, anim, 5, 0);

    if (*anim & 2) {
        s16 stateIndex;
        s32 *handlerSlot;

        if (sub_08014EF4(0x1388) == 1) {
            *(s32 *)(work + 0x10) = 0x2000;
        } else {
            *(s32 *)(work + 0x10) = 0xFFFFE000;
        }

        stateIndex = *(s16 *)((u8 *)self + 0x22);
        *(u8 *)((u8 *)self + stateIndex * 2 + 0x19) = 0;

        handlerSlot = (s32 *)0x08671BD0;
        {
            void *statePtr = (u8 *)self + 0x18;
            void *slotPtr = (u8 *)self + 0x22;
            sub_080C31E8(statePtr, slotPtr, 0, *handlerSlot);
        }
    }
}
