/* One frame of a travelling object: advance its animation, lengthen its step
 * (radius) by 0x800, clamp the radius at 0x18000, then move it along its angle. */
void sub_080B5ACC(void *self) {
    s32 animId = *(s32 *)((u8 *)self + 0x38);
    void *mover = *(void **)((u8 *)self + 0x3C);
    s32 step;
    stepAnimationTrack(animId, (u8 *)mover + 0x34);
    step = *(s32 *)((u8 *)self + 0x6C) + 0x800;
    *(s32 *)((u8 *)self + 0x6C) = step;
    if (step > 0x17FFF) {
        *(s32 *)((u8 *)self + 0x6C) = 0x18000;
    }
    sub_080146D0(mover, *(s32 *)((u8 *)self + 0x7C), *(s32 *)((u8 *)self + 0x6C));
    advanceMotion(mover, 0);
}
