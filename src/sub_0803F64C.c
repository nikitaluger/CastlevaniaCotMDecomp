s32 sub_08014990(void *);
void sub_080C31E4(void *, void *, s32);

/* Dash horizontally toward the target; after 20 frames stop, reset the step
 * counter and advance the command stream. */
void sub_0803F64C(void *obj) {
    s32 gfx = *(s32 *)((u8 *)obj + 0x38);
    void *state = *(void **)((u8 *)obj + 0x3C);
    if (sub_08014990(gfx) > 0)
        *(s32 *)((u8 *)state + 0x10) = 0x80 << 9;
    else
        *(s32 *)((u8 *)state + 0x10) = (s32)0xFFFF0000;
    if ((u32)((u8 *)((u8 *)obj + *(s16 *)((u8 *)obj + 0x22) * 2))[0x19] > 0x14) {
        *(s32 *)((u8 *)state + 0x10) = 0;
        ((u8 *)((u8 *)obj + *(s16 *)((u8 *)obj + 0x22) * 2))[0x19] = 0;
        {
            s32 *stepHandler;
            stepHandler = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)obj + 0x18, (u8 *)obj + 0x22, *stepHandler);
        }
    }
}
