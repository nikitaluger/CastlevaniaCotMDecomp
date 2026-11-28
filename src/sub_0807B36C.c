extern u32 gMainObjTimerCallbacks;

/* Global run state: offsets are the fields this entity system reads. */
struct GameState {
    u8 _0[0x10];
    s32 f10;
    u8 _14[0x14ED - 0x14];
    u8 f14ED;
    u8 _14EE[0x1510 - 0x14EE];
    u8 f1510;
    u8 _1511[0x173A - 0x1511];
    u8 f173A;
    u8 _173B[0x18C2 - 0x173B];
    u16 f18C2;
};
extern struct GameState gMainWorkspace;
extern s32 stepDelayTimer(s32, void *);
extern s32 applyAreaSpecialBehavior(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Timed entity-motion update: consult the area's special-motion rules, copy the
 * shared state word into the entity's object, count down a per-move timer that
 * fires a table-driven effect on expiry, snap the position to the grid and
 * invoke the entity callback when the global state ends the move. */
void sub_0807B36C(void *entity) {
    void *moveData;
    void *pos;
    void *obj;
    s32 countdown;
    struct GameState *state;
    s32 *fxTable;

    moveData = *(void **)((u8 *)entity + 0x6C);
    pos = (void *)((u8 *)moveData + 4);
    obj = *(void **)((u8 *)entity + 0x38);
    if (applyAreaSpecialBehavior(entity, obj, pos) > 0) {
        sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
        return;
    }
    state = &gMainWorkspace;
    *(u16 *)obj = state->f18C2;
    countdown = *(s32 *)((u8 *)pos + 0x10) - 1;
    *(s32 *)((u8 *)pos + 0x10) = countdown;
    if (countdown == 0) {
        countdown = 0xFFFD0000;
        *(s32 *)((u8 *)pos + 8) = countdown;
        *(s32 *)((u8 *)pos + 0x0C) = 0x80000;
        *(s8 *)((u8 *)*(void **)((u8 *)pos + 0x2C) + 1) = (s8)(1 & state->f1510);
        *(s8 *)((u8 *)*(void **)((u8 *)pos + 0x30) + 1) = (s8)(1 & state->f1510);
        *(s8 *)((u8 *)*(void **)((u8 *)pos + 0x34) + 1) = (s8)(1 & state->f1510);
        *((u8 *)entity + ((*(s16 *)((u8 *)entity + 0x22)) * 2) + 0x19) = 0;
        fxTable = &gMainObjTimerCallbacks;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *fxTable);
    }
    stepDelayTimer((s32)moveData + 0x20, obj);
    sub_0806D588(obj, pos);
    if (state->f173A == 0x1C || (state->f14ED == 0 && state->f10 != 0)) {
        sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
    }
}
