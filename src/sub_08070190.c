s32 sub_08003740(s32, s32);
s32 sub_0806D35C(void *, s32, s32);
s32 sub_0806D588(s32, s32);
s32 sub_080C31E0(void *, s32);

/* If the effect passes its visibility check, update its screen position from
 * the world vector, run its delay timer, and dispatch the entity's callback
 * when the timer is spent. */
void sub_08070190(void *entity) {
    s32 target;
    s32 vec;
    s32 state;

    state = *(s32 *)((u8 *)entity + 0x6C);
    vec = state + 4;
    target = *(s32 *)((u8 *)entity + 0x38);
    if (sub_0806D35C(entity, target, vec) == 0) {
        sub_0806D588(target, vec);
        if (sub_08003740(state + 0x30, target) == 0) {
            sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
        }
    }
}
