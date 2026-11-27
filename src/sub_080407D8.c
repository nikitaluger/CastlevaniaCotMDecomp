void sub_080144D8(void *, void *);
void sub_080144FC(void *, void *);
void sub_080C31E0(void *, void *);
void advanceMotion(void *, s32);

/* Run one step of an entity's phased AI: set up its view sprite, dispatch the
 * handler chosen by the current phase's state byte out of the behavior table
 * at +0x14, then place the sprite in the world. */
void sub_080407D8(void *arg0) {
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    sub_080144D8(arg0, sprite);
    *(void **)((u8 *)arg0 + 0x14) = (void *)0x0866E0F8;
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) + 1);
    {
        u8 *phase = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        phase[0x19] = (u8)(phase[0x19] + 1);
        {
            s32 offset = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
            u8 *states = (u8 *)arg0 + 0x18;
            u8 state = *(states + offset);
            void **handlers = *(void **)((u8 *)arg0 + 0x14);
            void *handler = handlers[state];
            sub_080C31E0(arg0, handler);
        }
    }
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) - 1);
    sub_080144FC(arg0, sprite);
}
