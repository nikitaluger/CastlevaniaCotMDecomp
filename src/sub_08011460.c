extern s32 sub_08010E70(s32, void *, s32, s32);

/* Advance the animation held in `anim` by `delta` ticks, using the frame table
 * stored in the entity's animation control block. */
void sub_08011460(s32 entity, void *anim, s32 delta) {
    sub_08010E70(entity, anim,
        *(*(s32 **)((s8 *)anim + 8)) + (*(s16 *)((s8 *)anim + 0xE) * 4),
        delta);
}
