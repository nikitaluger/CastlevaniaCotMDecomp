extern void *D_08671BD0;
extern void sub_0806AB04(void *, void *, void *, void *);
extern s32 sub_08003740(void *, void *);
extern u16 sub_08065CC8(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void *sub_0806D2A0(void *, s32, s32, s32);
extern void sub_0806D7B4(void *, s32);
extern void sub_08084CBC(void *, void *);
extern void sub_080C31E8(void *, void *, u32, void *);
extern u16 sub_0806BCD8(void *, void *, void *, void *);

struct SGlobals { u8 pad[0x1824]; u32 f1824; };
extern struct SGlobals D_02025FF0;

/* Per-frame actor update: refresh camera/mode state and tick the actor's timer;
 * on expiry, clear the current script step, fire the type's callback and spawn
 * a cooldown child, then run the collision check and common follow-up updates. */
void sub_080660A4(u8 *actor)
{
    u8 *state = *((u8 **)(actor + 0x6C));
    u8 *objTail = state + 4;
    u8 *position = *((u8 **)(actor + 0x38));
    u8 *obj = objTail;
    s32 timerResult;

    if (sub_0806C4B4(obj, objTail) != 0)
    {
        return;
    }
    sub_0806C5EC(actor, position, obj, obj);
    sub_0806AB04(actor, position, obj, obj);
    sub_0806A884(position, obj);
    timerResult = sub_08003740(state + 0x2C, position);
    if (timerResult == 0)
    {
        *((u8 *)(((s16)*((s16 *)(actor + 0x22))) * 2 + (u32)actor) + 0x19) = timerResult;
        {
            void **callback = &D_08671BD0;
            u8 *cbArgA = actor + 0x18;
            u8 *cbArgB = actor + 0x22;
            u16 callbackValue = sub_08065CC8(actor, position, obj, obj);
            sub_080C31E8(cbArgA, cbArgB, callbackValue, *callback);
        }
        D_02025FF0.f1824 = timerResult;
        *((u32 *)(state + 0xA0)) = timerResult;
        sub_08084CBC(actor, obj);
        {
            u32 *accelAddr = (u32 *)(state + 0xC4);
            u32 accel = *accelAddr;
            if (accel != 0)
            {
                void *spawned;
                sub_0806D7B4(obj, accel << 16);
                spawned = sub_0806D2A0(actor, 0x3C, 0xA, 0x12);
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
            void **callback = &D_08671BD0;
            sub_080C31E8(actor + 0x18, actor + 0x22, *((u32 *)(objTail + 0xC4)), *callback);
        }
        D_02025FF0.f1824 = 0;
        sub_08003740(objTail + 0x28, position);
    }
    sub_0806C6B0(actor, position, objTail, obj);
}
