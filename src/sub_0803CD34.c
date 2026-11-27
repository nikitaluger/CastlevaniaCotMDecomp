void stepAnimationTrack(s32, void *);
void setAnimationFrame(s32, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Animation-end update: clears the work's auxiliary state bytes, steps the
 * animation, and when that animation reports completion (bit 1) switches to
 * animation 4, marks the state finished and advances the entity's script. */
void sub_0803CD34(void *arg0) {
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *anim = work + 0x34;
    u8 *state = *(u8 **)(work + 0x28);
    s32 zero;
    zero = 0;
    *(state + 2) = zero;
    *(u8 *)(*(u32 *)(work + 0x28) + 3) = zero;
    stepAnimationTrack((s32)sprite, anim);
    if (2 & *anim) {
        void **scriptHandlers;
        setAnimationFrame((s32)sprite, anim, 4, 0);
        *(u8 *)(*(u32 *)(work + 0x28) + 2) = 8;
        *(u8 *)(*(u32 *)(work + 0x28) + 3) = 1;
        ((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2))[0x19] = zero;
        scriptHandlers = (void **)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*scriptHandlers);
    }
}
