s32 stepAnimationTrack(s32 sprite, s32 block);
s32 advanceMotion(s32 state, s32 accel);

/* Apply this entity's state block to its sprite, then integrate the state's
 * physics using the acceleration held in the entity. */
void sub_080AA5C0(void *entity)
{
    s32 state;
    s32 sprite;

    sprite = *(s32 *)((s8 *)entity + 0x38);
    state = *(s32 *)((s8 *)entity + 0x3C);
    stepAnimationTrack(sprite, state + 0x34);
    advanceMotion(state, *(s32 *)((s8 *)entity + 0x6C));
}
