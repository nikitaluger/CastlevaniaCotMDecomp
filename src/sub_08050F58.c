extern void stepAnimationTrack(void *animHandle, void *anim);
extern void sub_08051FD8(void *self, void *angles);

/* Initialises the object's animation: plays the animation state at +0x34 of the
 * data block (+0x3C) on the animation handle at +0x38, then starts the angle
 * sweep described by the block at +0x48. */
void sub_08050F58(u8 *self)
{
    void *animHandle = *(void **)(self + 0x38);
    u8 *data = *(u8 **)(self + 0x3C);
    u8 *anim = data + 0x34;
    data += 0x48;
    stepAnimationTrack(animHandle, anim);
    sub_08051FD8(self, data);
}
