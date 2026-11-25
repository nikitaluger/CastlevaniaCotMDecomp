void sub_08011368(s32, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Advance the actor's model animation to frame 0x1D and tick the frame timer
   at field+0x48 down; when it expires, clear the step's progress and run the
   0x08671BB0 script handler. */
void sub_0801D584(void *arg0) {
    void *model = *(void **)((u8 *)arg0 + 0x38);
    u8 *field = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *anim = field + 0x34;
    u16 *timer = (u16 *)(field + 0x48);
    s32 remaining;
    sub_08011368((s32)model, anim, 0x1D, 1);
    remaining = *timer - 1;
    *timer = remaining;
    if ((s32)(remaining << 0x10) < 0) {
        void **scriptFn;
        ((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2))[0x19] = 0;
        scriptFn = (void **)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*scriptFn);
    }
}
