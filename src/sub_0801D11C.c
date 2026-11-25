void sub_08011368(s32, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Play sprite animation 0x1A on the entity (animation state at work+0x34); if
 * the animation's finished flag (bit 1 of its state byte) is set, clear the
 * current step byte and advance the entity's command script. */
void sub_08019870(void *arg0) {
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    sub_08011368((s32)sprite, work + 0x34, 0x1A, 0);
    if (2 & work[0x34]) {
        void **scriptTable;
        ((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2))[0x19] = 0;
        scriptTable = (void **)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*scriptTable);
    }
}

/* Unregister this actor from the 9-entry active-slot table at +0x80 of the
 * object referenced through self+0x8C, unless the actor is flagged as
 * persistent (bit 0 of its +0x64 status word). */
void sub_0801D11C(void *arg0) {
    if (!(1 & *(u16 *)((u8 *)arg0 + 0x64))) {
        u32 *slots = *(u32 **)(*(u8 **)((u8 *)arg0 + 0x8C) + 0x3C);
        u32 zero = 0;
        u32 *slot = slots + 0x20;
        s32 i = 9;
        do {
            if (*slot == (u32)arg0) *slot = zero;
            slot++;
        } while (--i >= 0);
    }
}

/* Advance the actor's model animation by 0x1A frames; if its restart flag is
 * set, reload the 0x1E timer, clear the level's repeat counter and run the
 * handler at 0x08671BB0. */
void sub_08019D90(void *arg0) {
    void *model = *(void **)((u8 *)arg0 + 0x38);
    u8 *anim = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *animFlags = anim + 0x34;
    u16 *timer = (u16 *)(anim + 0x48);
    sub_08011368((s32)model, animFlags, 0x1A, 0);
    if (2 & *animFlags) {
        s32 zero = 0;
        void **handlerTable;
        *timer = 0x1E;
        ((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2))[0x19] = zero;
        handlerTable = (void **)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*handlerTable);
    }
}

/* Advance the actor's model animation to frame 0x1D and tick the frame timer
   at field+0x48 down; when it expires, clear the step's progress and run the
   0x08671BB0 script handler. */
void sub_08019DE0(void *arg0) {
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
