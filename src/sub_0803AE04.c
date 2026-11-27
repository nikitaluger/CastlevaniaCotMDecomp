extern void sub_080C31E4(void *, void *, s32);
extern void advanceMotion(void *, s32); /* integrates x/y position from velocity, then applies gravity */
extern void stepAnimationTrack(s32, void *); /* updates the animation of the object's physics body */

/* Per-frame step: integrates the object's position and animation, then, once the
 * current command's 15-frame wait has elapsed, resets the counter and advances
 * the command script. */
void sub_0803AE04(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 objId = *(s32 *)(self + 0x38);
    u8 *phys = *(u8 **)(self + 0x3C);
    u8 *anim = phys + 0x34;
    advanceMotion(phys, 0);
    stepAnimationTrack(objId, anim);
    {
        s16 slotIdx = *(s16 *)(self + 0x22);
        u8 *slot = (u8 *)((slotIdx << 1) + (u32)self);
        if (*(u8 *)(slot + 0x19) == 0x0F) {
            s32 *lit;
            *(u8 *)(slot + 0x19) = 0;
            lit = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *lit);
        }
    }
}
