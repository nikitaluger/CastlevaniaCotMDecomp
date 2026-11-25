void sub_080144D8(void *, void *);
void sub_080144FC(void *, void *);
void sub_080C31E0(void *, void *);

/* Advance to the next script step (state table 0x0866DF34): stamp the step on
 * the sprite, bump and mark the step counter, dispatch the step's handler, then
 * reposition the sprite on screen. */
void sub_0803A0DC(void *arg0) {
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    sub_080144D8(arg0, sprite);
    *(void **)((u8 *)arg0 + 0x14) = (void *)0x0866DF34;
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) + 1);
    {
        u8 *stepByte = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        stepByte[0x19] = (u8)(stepByte[0x19] + 1);
        {
            s32 stepOffset = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
            u8 *steps = (u8 *)arg0 + 0x18;
            u8 cmd = *(steps + stepOffset);
            void **table = *(void ***)((u8 *)arg0 + 0x14);
            void *handler = table[cmd];
            sub_080C31E0(arg0, handler);
        }
    }
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) - 1);
    sub_080144FC(arg0, sprite);
}
