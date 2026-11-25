s32 sub_08003740(s32, s32);
/* Check the effect's delay timer: if it is already spent, dispatch the entity's
 * callback; otherwise tick it again and refresh the target's screen position. */
void sub_0808A6A0(s32 entity) {
    s32 state;
    s32 vec;
    s32 target;
    s32 delay;
    s32 targetCopy;

    state = ((s32 *)(entity + 0x6C))[0];
    vec = state + 4;

    target = ((s32 *)(entity + 0x38))[0];
    delay = state + 0x20;

    targetCopy = target;

    if (sub_08003740(delay, target) == 0) {
        s32 callback = ((s32 *)(entity + 0x24))[0];
        sub_080C31E0(entity, callback);
        return;
    }

    sub_08003740(delay, target);
    sub_0806D588(target, vec);
}
