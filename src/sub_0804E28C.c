extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 sub_08014EF4(s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Play pose 3 and stand still; when the pose finishes, launch the entity up or
 * down (which way is picked by the timer), clear its state slot and detach it. */
void sub_0804E28C(void *arg0)
{
    u8 *body;
    void *gfx;
    u8 *anim;

    gfx = *(void **)((u8 *)arg0 + 0x38);
    body = *(u8 **)((u8 *)arg0 + 0x3C);
    anim = body + 0x34;

    setAnimationFrame(gfx, anim, 3, 0);
    *(s32 *)(body + 0x10) = 0;

    if (*anim & 2) {
        s16 stateIndex;
        s32 *handlerSlot;

        if (sub_08014EF4(0x1388) == 1) {
            *(s32 *)(body + 0x10) = 0x6000;
        } else {
            *(s32 *)(body + 0x10) = 0xFFFFA000;
        }

        stateIndex = *(s16 *)((u8 *)arg0 + 0x22);
        *(u8 *)((u8 *)arg0 + stateIndex * 2 + 0x19) = 0;

        handlerSlot = (s32 *)0x08671BD0;
        {
            void *statePtr = (u8 *)arg0 + 0x18;
            void *slotPtr = (u8 *)arg0 + 0x22;
            sub_080C31E8(statePtr, slotPtr, 0, *handlerSlot);
        }
    }
}
