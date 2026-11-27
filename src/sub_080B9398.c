extern void stepAnimationTrack(void *, void *);
extern void advanceMotion(void *, s32);

/* Refresh the sprite from its motion controller, add the object's +0x7C
 * input (scaled by <<13) to the controller's velocity, then integrate the
 * controller's motion with zero acceleration. */
void sub_080B9398(void *entity)
{
    u8 *self = entity;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *motion = *(u8 **)(self + 0x3C);
    stepAnimationTrack((void *)sprite, motion + 0x34);
    *(s32 *)(motion + 0x10) += *(s32 *)(self + 0x7C) << 13;
    advanceMotion(motion, 0);
}
