s32 stepDelayTimer(s32, s32);
void cullOffscreenEntity(void *, s32);
s32 checkGlobalStateChange(void *, s32, s32);
void sub_0806D588(s32, s32);
void sub_080719EC(void *, s32, s32);
void sub_080C31E0(void *, s32);

/* Per-frame update for a scripted object: skipped while a global state change
 * is pending; refreshes its contact state and drawn position, then retires the
 * object when its delay timer is idle or re-checks it against the active area. */
void sub_0806F9E0(void *entity) {
    s32 objectData;
    s32 parent;
    s32 state;

    state = *(s32 *)((u8 *)entity + 0x6C);
    objectData = state + 4;
    parent = *(s32 *)((u8 *)entity + 0x38);
    if (checkGlobalStateChange(entity, parent, objectData) == 0) {
        sub_080719EC(entity, objectData, objectData);
        sub_0806D588(parent, objectData);
        if (stepDelayTimer(state + 0x30, parent) == 0) {
            sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
            return;
        }
        cullOffscreenEntity(entity, parent);
    }
}
