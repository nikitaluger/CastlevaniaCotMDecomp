extern void sub_08011368(void *, void *, s32, s32);

/* Animation step: put the sprite on frame 0x0F in mode 1, then decrement the
 * controller's frame timer, clamping it at zero. */
void sub_0801EA98(void *arg0)
{
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    void *motion = *(void **)((u8 *)arg0 + 0x3C);
    void *anim = (u8 *)motion + 0x34;
    u16 *timer = (u16 *)((u8 *)motion + 0x48);
    sub_08011368(sprite, anim, 0x0F, 1);
    if ((s16)(--*timer) < 0)
        *timer = 0;
}
