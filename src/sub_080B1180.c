extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

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
