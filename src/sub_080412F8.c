extern void stepAnimationTrack(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080415D4(s32, s32, void *, void *);

/* Advance the enemy's animation; once the animation reports completion (bit 1
 * of its status byte), switch it into the idle action, clear the current script
 * byte and advance the script by one instruction. */
void sub_080412F8(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 owner = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animator = work + 0x34;
    s32 *advanceFunc;
    stepAnimationTrack((void *)owner, (void *)animator);
    if (*(u8 *)animator & 2) {
        sub_080415D4(0, owner, (void *)work, (void *)animator);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        advanceFunc = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *advanceFunc);
    }
}
