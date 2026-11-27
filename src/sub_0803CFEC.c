extern void stepAnimationTrack(s32, void *);
extern void sub_080C31E0(void *, s32);

/* Clear the two tile indices of the entity's sub-object record, advance its
 * animation by one frame, and on animation end switch the entity to the next
 * script state. */
void sub_0803CFEC(void *entity) {
    u8 *self = (u8 *)entity;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    {
        u8 *part = *(u8 **)(work + 0x28);
        u8 zero = 0;
        part[2] = zero;
        (*(u8 **)(work + 0x28))[3] = zero;
    }
    stepAnimationTrack(sprite, anim);
    if (anim[0] & 2) {
        sub_080C31E0(entity, *(s32 *)(self + 0x24));
    }
}
