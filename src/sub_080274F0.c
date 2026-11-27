extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 divInt32(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 sub_08014A04(void *, s32, s32, s32);
extern void sub_08014B1C(void *, void *, s32, s32);
extern void sub_08014DB4(void *, void *, s32, s32);
extern void sub_08027A4C(void *, s32, s32 *, s32 *);

extern s32 gTrigFuncPtr[];
extern s32 gScriptStepCallbackTable[];
extern u8 gMainWorkspace[];

void sub_0802754C(void *arg0) {
    s32 sp8;
    s32 sp4;
    void *temp_r5;
    s32 *lit;

    temp_r5 = *(void **)((u8 *)arg0 + 0x3C);
    sub_08027A4C(arg0, *(s32 *)((u8 *)temp_r5 + 0x50), &sp4, &sp8);
    if (sub_08014A04(temp_r5, sp4, sp8, 0xC0000) == 1) {
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
        lit = gScriptStepCallbackTable;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *lit);
        return;
    }
    sub_08014B1C(temp_r5, (u8 *)temp_r5 + 0x74, sp4, sp8);
}

/*
 * Script step: steer the work body toward the target position held in global
 * state; when the movement's done flag is set, clear this step's flag and run
 * the next-step callback.
 */
void sub_080274F0(void *actor) {
    void *work;
    u8 *state;
    s32 targetX, targetY;
    s32 *stepCallback;

    work = *(void **)((u8 *)actor + 0x3C);
    state = gMainWorkspace;
    targetX = *(s32 *)(state + 0x174C);
    targetY = *(s32 *)(state + 0x1750);
    sub_08014DB4(work, (u8 *)work + 0x74, targetX, targetY);
    if (4 & *(u16 *)((u8 *)work + 0x8C)) {
        *(u8 *)((u8 *)actor + *(s16 *)((u8 *)actor + 0x22) * 2 + 0x19) = 0;
        stepCallback = gScriptStepCallbackTable;
        sub_080C31E4((u8 *)actor + 0x18, (u8 *)actor + 0x22, *stepCallback);
    }
}
