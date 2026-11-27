extern void stepAnimationTrack(void *animHandle, void *anim);
extern void moveEntityWithCollision(void *move, s32 step);

/* Starts the actor's animation (state at +0x34) on the animation handle at
 * +0x38, then starts its movement state (+0x3C) moving by 0xB60 units. */
void sub_08051C00(void *self) {
    void *animHandle = *(void **)((u8 *)self + 0x38);
    void *move = *(void **)((u8 *)self + 0x3C);
    stepAnimationTrack(animHandle, (u8 *)move + 0x34);
    moveEntityWithCollision(move, 0xB60);
}
