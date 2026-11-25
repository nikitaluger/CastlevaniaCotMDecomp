void sub_080144D8(void *, void *);
void sub_080144FC(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080161F0(void);
void sub_08015974(void);
void sub_08016678(void *);
void _call_via_r1(void *, void *);

/* Release this actor: unlink its three effect slots and its extra object from
 * their global lists, finalize its sub-object, then call its cleanup handler. */
void sub_08035D6C(void *arg0) {
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *state = work + 0x48;
    if (*(s32 *)(work + 0x28) != 0) sub_080161F0();
    if (*(s32 *)(work + 0x48) != 0) sub_080161F0();
    if (*(s32 *)(state + 4) != 0) sub_080161F0();
    if (*(s32 *)(work + 0x2C) != 0) sub_08015974();
    sub_08016678(arg0);
    _call_via_r1(arg0, *(void **)(work + 0x24));
}

/* Advance to the next script step (state table 0x0866DDF0): stamp the step on
 * the sprite, bump and mark the step counter, dispatch the step's handler, then
 * reposition the sprite on screen. */
void sub_0803617C(void *arg0) {
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    sub_080144D8(arg0, sprite);
    *(void **)((u8 *)arg0 + 0x14) = (void *)0x0866DDF0;
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

/* Advance to the next script step (state table 0x0866DDC4): stamp the step on
 * the sprite, bump and mark the step counter, dispatch the step's handler, then
 * reposition the sprite on screen. */
void sub_0803569C(void *arg0) {
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    sub_080144D8(arg0, sprite);
    *(void **)((u8 *)arg0 + 0x14) = (void *)0x0866DDC4;
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

/* Advance to the next script step (state table 0x0866DE34): stamp the step on
 * the sprite, bump and mark the step counter, dispatch the step's handler, then
 * reposition the sprite on screen. */
void sub_08036E60(void *arg0) {
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    sub_080144D8(arg0, sprite);
    *(void **)((u8 *)arg0 + 0x14) = (void *)0x0866DE34;
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
