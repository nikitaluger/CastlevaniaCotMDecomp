char stepAnimationTrack(s32 sprite, s32 block);
s32 advanceMotion(s32 state, s32 accel);

/* Integrate the entity's state physics with zero acceleration, then apply the
 * resulting state block to its sprite. */
void sub_080A4858(void *entity)
{
    s32 stateBlock;
    s32 state;
    s8 *spritePtr;
    s32 sprite;

    spritePtr = (s8 *)entity + 0x38;
    sprite = *(s32 *)spritePtr;
    state = *(s32 *)((s8 *)entity + 0x3C);
    stateBlock = state + 0x34;
    advanceMotion(state, 0);
    stepAnimationTrack(sprite, stateBlock);
}
