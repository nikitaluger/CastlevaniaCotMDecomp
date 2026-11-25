extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Advance the actor's script in place: clear the work's +0x4F flag and the
 * current step's substep counter, advance one script step, bump the new
 * substep and immediately dispatch that command from the actor's table. */
void sub_080B0EC4(void *arg0)
{
    u8 *self = arg0;
    u8 *stepBase;
    s32 *scriptAdvance;
    u8 *workFlags = (u8 *)*(void **)(self + 0x3C) + 0x48;
    workFlags[7] = 0;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    scriptAdvance = (s32 *)0x08671BB0;
    stepBase = self + 0x18;
    sub_080C31E4(stepBase, self + 0x22, *scriptAdvance);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    stepBase += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(s32 *)(*(u32 *)(self + 0x14) + *(u8 *)stepBase * 4));
}

extern void sub_080B1960(void *, void *);

/* Wait-with-sprite step: sync the sprite (self+0x4C) with the work object
 * (self+0x3C) every frame; after 60 frames, once the sprite's step byte at
 * +0x25 is back to 0, clear the substep and advance the script. */
void sub_080B1180(void *arg0)
{
    u8 *self = arg0;
    void *work = *(void **)(self + 0x3C);
    void *sprite = *(void **)(self + 0x4C);
    sub_080B1960(work, sprite);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) > 0x3C) {
        u8 stepState = *(u8 *)((u8 *)sprite + 0x25);
        if (stepState == 0) {
            s32 *scriptAdvance;
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = stepState;
            scriptAdvance = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *scriptAdvance);
        }
    }
}
