/* Per-frame update for an actor driven by a work state: advances a table-clamped value,
 * handles its mode-1 action and input checks, fires the resulting script events, and
 * records the event id for the next frame. */
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, s32, void *, void *);
extern void sub_0806BA20(s32, void *, void *);
extern void sub_0806B104(s32, void *, void *);
extern void sub_0806AB04(void *, s32, void *, void *);
extern void sub_08005E80(s32);
extern void spawnKind2CEntity(void *, s32, s32, s32);
extern void sub_0806A884(s32, void *);
extern s32 stepDelayTimer(void *, s32);
extern void sub_0806A7AC(s32, void *, s32);
extern void sub_080849A4(void *, void *);
extern u16 sub_0806BCD8(void *, s32, void *, void *);
extern void sub_0806C6B0(void *, s32, void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
struct WorkState { u8 _0[8]; s32 f8; s32 fC; u8 _10[0x40-0x10]; s32 f40; s32 f44; u8 _48[4]; s32 f4C; s32 f50; s32 f54; };
struct Work { u8 _0[0xC8]; s32 eventId; };

void sub_08064CE0(u8 *arg0) {
    u8 *checkPtr;
    u8 *work = *(u8 **)(arg0 + 0x6C);
    u8 *state = work + 4;
    s32 sprite = *(s32 *)(arg0 + 0x38);
    s32 result = syncViewPosition(state, state);
    s32 base, idx;

    if (result != 0) return;

    resetActionResultState(arg0, sprite, state, state);
    sub_0806BA20(sprite, state, state);
    base = 0x080E03A0;
    idx = ((struct WorkState *)state)->f44 * 0x58;
    ((struct WorkState *)state)->fC = ((struct WorkState *)state)->fC + *(s32 *)(base + idx);
    base += 4;
    {
        s32 maxValue = *(s32 *)(base + idx);
        if (((struct WorkState *)state)->fC > maxValue) ((struct WorkState *)state)->fC = maxValue;
    }
    sub_0806B104(sprite, state, state);
    sub_0806AB04(arg0, sprite, state, state);
    if (((struct WorkState *)state)->f40 == 1) {
        u8 *stepPtr;
        s32 *callback;
        sub_08005E80(0x67);
        ((struct WorkState *)state)->f4C = result;
        ((struct WorkState *)state)->f50 = result;
        ((struct WorkState *)state)->f54 = result;
        ((struct WorkState *)state)->f8 = result;
        spawnKind2CEntity(arg0, 9, *(s32 *)(work + 4), *(s32 *)(state + 4));
        stepPtr = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        *(u8 *)(stepPtr + 0x19) = result;
        callback = (s32 *)0x08671BD0;
        sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0x12, *callback);
    }
    sub_0806A884(sprite, state);
    checkPtr = work + 0x2C;
    if (stepDelayTimer(checkPtr, sprite) == 0) {
        u8 *stepPtr;
        s32 *callback;
        sub_0806A7AC(sprite, state, 0x10);
        stepDelayTimer(checkPtr, sprite);
        stepPtr = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        *(u8 *)(stepPtr + 0x19) = result;
        callback = (s32 *)0x08671BD0;
        sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 3, *callback);
    }
    sub_080849A4(arg0, state);
    *(s32 *)((u8 *)work + 0xC8) = (u16)sub_0806BCD8(arg0, sprite, state, state);
    if (((struct Work *)work)->eventId != 0) {
        u8 *stepPtr;
        s32 *callback;
        stepDelayTimer(checkPtr, sprite);
        stepPtr = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        *(u8 *)(stepPtr + 0x19) = result;
        callback = (s32 *)0x08671BD0;
        sub_080C31E8(arg0 + 0x18, arg0 + 0x22, ((struct Work *)work)->eventId, *callback);
    }
    sub_0806C6B0(arg0, sprite, state, state);
}
