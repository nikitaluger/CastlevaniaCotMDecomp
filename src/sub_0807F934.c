s32 sub_0806D35C(void *, s32, void *);
s32 stepDelayTimer(s32, s32);
void sub_0807F588(void *, void *);
void startEffectTimer(s32, s32, s32);
void sub_0806D588(s32, void *);
void sub_0808DC40(s32, s32, s32);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);

extern u8 D_084EC108[];
extern s32 gMainObjTimerCallbacks;

struct S_02025FF0 {
    u8 pad0[0x14ED];
    u8 gameMode;
    u8 pad14EE[0x14F4 - 0x14EE];
    s32 field14F4;
    s32 field14F8;
    s32 field14FC;
    s32 field1500;
};
extern struct S_02025FF0 gMainWorkspace;

/* Handle an entity driven by the global area behavior: apply the current area
 * action, and when there is none, run its step timer/callback. */
void sub_0807F934(u8 *entity)
{
    u8 *comp = *(u8 **)(entity + 0x6C);
    u8 *ctx = comp + 4;
    s32 stateObj = *(s32 *)(entity + 0x38);
    s32 action = sub_0806D35C(entity, stateObj, ctx);
    if ((u32)(action - 2) <= 1) {
        sub_0807F588(entity, ctx);
    }
    if (action == 0) {
        u8 *timer = comp + 0x20;
        s32 result = stepDelayTimer((s32)timer, stateObj);
        if (result == 0) {
            startEffectTimer((s32)timer, 0, (s32)D_084EC108);
            gMainWorkspace.field14F4 = gMainWorkspace.field14F8 << 6;
            gMainWorkspace.field14F8 = result;
            *(u8 *)(entity + (s32)*(s16 *)(entity + 0x22) * 2 + 0x19) = (u8)result;
            {
                s32 *hookSlot = &gMainObjTimerCallbacks;
                sub_080C31E4(entity + 0x18, entity + 0x22, *hookSlot);
            }
        }
        stepDelayTimer((s32)timer, stateObj);
        sub_0806D588(stateObj, ctx);
        gMainWorkspace.field14FC = *(s32 *)(comp + 4);
        gMainWorkspace.field1500 = *(s32 *)(ctx + 4);
        if (gMainWorkspace.gameMode != 0x8A) {
            sub_0808DC40(*(s32 *)(comp + 4), *(s32 *)(ctx + 4), 0);
            sub_080C31E0(entity, *(s32 *)(entity + 0x24));
        }
    }
}
