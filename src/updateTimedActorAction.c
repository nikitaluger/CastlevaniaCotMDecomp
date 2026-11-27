extern void *gScriptStepCallbacks;
extern void sub_0806AB04(void *, void *, void *, void *);
extern s32 stepDelayTimer(void *, void *);
extern u16 sub_08065CC8(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern s32 syncViewPosition(void *, void *);
extern void resetActionResultState(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void *spawnEntity(void *, s32, s32, s32);
extern void sub_0806D7B4(void *, s32);
extern void spawnRoom34Object(void *, void *);
extern void sub_080C31E8(void *, void *, u32, void *);
extern u16 sub_0806BCD8(void *, void *, void *, void *);

struct SGlobals { u8 pad[0x1824]; u32 f1824; };
extern struct SGlobals gMainWorkspace;

/* Per-frame actor update: refresh camera/mode state and tick the actor's timer;
 * on expiry, clear the current script step, fire the type's callback and spawn
 * a cooldown child, then run the collision check and common follow-up updates. */
void updateTimedActorAction(u8 *actor)
{
    u8 *state = *((u8 **)(actor + 0x6C));
    u8 *objTail = state + 4;
    u8 *position = *((u8 **)(actor + 0x38));
    u8 *obj = objTail;
    s32 timerResult;

    if (syncViewPosition(obj, objTail) != 0)
    {
        return;
    }
    resetActionResultState(actor, position, obj, obj);
    sub_0806AB04(actor, position, obj, obj);
    sub_0806A884(position, obj);
    timerResult = stepDelayTimer(state + 0x2C, position);
    if (timerResult == 0)
    {
        *((u8 *)(((s16)*((s16 *)(actor + 0x22))) * 2 + (u32)actor) + 0x19) = timerResult;
        {
            void **callback = &gScriptStepCallbacks;
            u8 *cbArgA = actor + 0x18;
            u8 *cbArgB = actor + 0x22;
            u16 callbackValue = sub_08065CC8(actor, position, obj, obj);
            sub_080C31E8(cbArgA, cbArgB, callbackValue, *callback);
        }
        gMainWorkspace.f1824 = timerResult;
        *((u32 *)(state + 0xA0)) = timerResult;
        spawnRoom34Object(actor, obj);
        {
            u32 *accelAddr = (u32 *)(state + 0xC4);
            u32 accel = *accelAddr;
            if (accel != 0)
            {
                void *spawned;
                sub_0806D7B4(obj, accel << 16);
                spawned = spawnEntity(actor, 0x3C, 0xA, 0x12);
                if (spawned != 0)
                {
                    *((u16 *)((u8 *)spawned + 0x7C)) = 1;
                }
                *accelAddr = timerResult;
            }
        }
    }
    *((u32 *)(objTail + 0xC4)) = sub_0806BCD8(actor, position, objTail, obj);
    if (*((u32 *)(objTail + 0xC4)) != 0)
    {
        *((u8 *)(((s16)*((s16 *)(actor + 0x22))) * 2 + (u32)actor) + 0x19) = 0;
        {
            void **callback = &gScriptStepCallbacks;
            sub_080C31E8(actor + 0x18, actor + 0x22, *((u32 *)(objTail + 0xC4)), *callback);
        }
        gMainWorkspace.f1824 = 0;
        stepDelayTimer(objTail + 0x28, position);
    }
    sub_0806C6B0(actor, position, objTail, obj);
}
