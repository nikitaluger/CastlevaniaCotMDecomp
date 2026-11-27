void stepAnimationTrack(void *entity, void *track);

/* Animation tick: step the animation track embedded at +0x34 of the actor's
 * work state (+0x3C) for the entity at +0x38. */
void sub_080B2978(void *self) {
    stepAnimationTrack(*(s32 *)((u8 *)self + 0x38), *(s32 *)((u8 *)self + 0x3C) + 0x34);
}
