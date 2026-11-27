struct ActorUpdate {
    u8 _0[0x22]; s16 step; u8 _24[0x14];
    u8 *parent; u8 _3C[0x30]; u8 *state;
};
struct ActorStateData {
    u8 _0[4]; u32 param; u8 _08[0x24]; u32 field2C;
};
struct Actor {
    u8 _0[4]; u32 param; u32 counter; u32 energy;
    u8 _10[0x30]; u32 mode; u32 kind; u8 _48[4];
    u32 timerA; u32 timerB; u32 timerC;
};
struct ActorParam { u32 value; u32 limit; u8 _8[0x50]; };
extern struct ActorParam D_080E03A0[];
extern u32 gScriptStepCallbacks;
extern u32 gMenuScriptCallback;

extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void sub_08005E80(s32);
extern void spawnKind2CEntity(void *, s32, u32, u32);
extern void sub_080C31E8(void *, void *, s32, u32);
extern void sub_0806D588(void *, void *);
extern void sub_0806A884(void *, void *);
extern u32 stepDelayTimer(void *, void *);
extern void sub_0806A7AC(void *, void *, s32);
extern void sub_0806C6B0(void *, void *, void *, void *);

/* Updates one actor for a frame: clamps its energy to the per-kind limit,
 * runs the mode-1 reset, applies position/contact fixes and the main update. */
void sub_08067A04(struct ActorUpdate *arg0) {
    struct ActorStateData *state = (struct ActorStateData *)arg0->state;
    struct Actor *actor = (struct Actor *)((u8 *)state + 4);
    u8 *parent = arg0->parent;
    s32 posMode = syncViewPosition(actor, actor);
    if (posMode == 0) {
        u8 *stepPtr;
        s32 value, limit;
        resetActionResultState(arg0, parent, actor, actor);
        value = actor->energy + D_080E03A0[actor->kind].value;
        actor->energy = value;
        limit = D_080E03A0[actor->kind].limit;
        if (value > limit) actor->energy = limit;
        sub_0806AB04(arg0, parent, actor, actor);
        if (actor->mode == 1) {
            sub_08005E80(0x67);
            actor->timerA = posMode;
            actor->timerB = posMode;
            actor->timerC = posMode;
            actor->counter = posMode;
            spawnKind2CEntity(arg0, 9, state->param, actor->param);
            stepPtr = (u8 *)((u32)(arg0->step * 2) + (u32)arg0);
            stepPtr[0x19] = posMode;
            {
                u32 *pd = &gScriptStepCallbacks;
                sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 1, *pd);
            }
        }
        sub_0806D588(parent, actor);
        sub_0806A884(parent, actor);
        {
            u8 *stateField = (u8 *)state + 0x2C;
            u32 result = stepDelayTimer(stateField, parent);
            if (result == 0) {
                sub_0806A7AC(parent, actor, 0x10);
                stepDelayTimer(stateField, parent);
                stepPtr = (u8 *)((u32)(arg0->step * 2) + (u32)arg0);
                stepPtr[0x17] = result;
                {
                    u32 *pd = &gMenuScriptCallback;
                    sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 3, *pd);
                }
            }
        }
        sub_0806C6B0(arg0, parent, actor, actor);
    }
}
