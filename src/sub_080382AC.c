void sub_080144D8(void *, void *);
void sub_080144FC(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080113A8(void *, void *);
void sub_08011EE8(void *, s32, s32);

/* Advance to the next script step (state table 0x0866DE68): stamp the step on
 * the sprite, bump and mark the step counter, dispatch the step's handler, then
 * reposition the sprite on screen. */
void sub_08037B28(void *arg0) {
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    sub_080144D8(arg0, sprite);
    *(void **)((u8 *)arg0 + 0x14) = (void *)0x0866DE68;
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) + 1);
    {
        u8 *stepByte = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        stepByte[0x19] = (u8)(stepByte[0x19] + 1);
        {
            s32 stepOffset = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
            u8 *steps = (u8 *)arg0 + 0x18;
            u8 cmd = *(steps + stepOffset);
            u8 **table = *(u8 **)((u8 *)arg0 + 0x14);
            void *handler = table[cmd];
            sub_080C31E0(arg0, handler);
        }
    }
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) - 1);
    sub_080144FC(arg0, sprite);
}

/* Advance to the next script step (state table 0x0866DE98): stamp the step on
 * the sprite, bump and mark the step counter, dispatch the step's handler, then
 * reposition the sprite on screen. */
void sub_080382AC(void *arg0) {
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    sub_080144D8(arg0, sprite);
    *(void **)((u8 *)arg0 + 0x14) = (void *)0x0866DE98;
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) + 1);
    {
        u8 *stepByte = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        stepByte[0x19] = (u8)(stepByte[0x19] + 1);
        {
            s32 stepOffset = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
            u8 *steps = (u8 *)arg0 + 0x18;
            u8 cmd = *(steps + stepOffset);
            u8 **table = *(u8 **)((u8 *)arg0 + 0x14);
            void *handler = table[cmd];
            sub_080C31E0(arg0, handler);
        }
    }
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) - 1);
    sub_080144FC(arg0, sprite);
}

/* Animation step: advance the sub-object's animator, then run its movement and
 * collision update with flags 0x16C1 and gravity 0xE<<12. */
void sub_0803895C(void *arg0) {
    s32 work = *(s32 *)((u8 *)arg0 + 0x3C);
    sub_080113A8(*(void **)((u8 *)arg0 + 0x38), (u8 *)work + 0x34);
    sub_08011EE8((void *)work, 0x16C1, 0xE0 << 12);
}

/* Advance to the next script step (state table 0x0866DEE0): stamp the step on
 * the sprite, bump and mark the step counter, dispatch the step's handler, then
 * reposition the sprite on screen. */
void sub_08038F44(void *arg0) {
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    sub_080144D8(arg0, sprite);
    *(void **)((u8 *)arg0 + 0x14) = (void *)0x0866DEE0;
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) + 1);
    {
        u8 *stepByte = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        stepByte[0x19] = (u8)(stepByte[0x19] + 1);
        {
            s32 stepOffset = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
            u8 *steps = (u8 *)arg0 + 0x18;
            u8 cmd = *(steps + stepOffset);
            u8 **table = *(u8 **)((u8 *)arg0 + 0x14);
            void *handler = table[cmd];
            sub_080C31E0(arg0, handler);
        }
    }
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) - 1);
    sub_080144FC(arg0, sprite);
}
