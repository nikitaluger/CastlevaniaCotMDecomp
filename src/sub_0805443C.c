extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallback;

struct S {
    s16 angle;
    u16 flags;
    u16 counter;
};

// Clamps this entity's angle to +/-0x4000, resetting its step state and dispatching the step callback.
void sub_0805443C(void *obj)
{
    struct S *angleState;
    s16 angle;

    angleState = (struct S *)((u8 *)*(void **)((u8 *)obj + 0x3C) + 0x48);
    angle = angleState->angle;

    if (angle > 0x3FFF) {
        angleState->angle = (s16)0x4000;
        angleState->flags = (u16)0;
        angleState->counter = 0x14;
        *(u8 *)((u8 *)obj + *(s16 *)((u8 *)obj + 0x22) * 2 + 0x19) = (u8)0;
        {
            s32 *p = &gMainObjTimerCallback;
            sub_080C31E4((u8 *)obj + 0x18, (u8 *)obj + 0x22, *p);
        }
    }
    else if (angle <= -0x4000) {
        angleState->angle = (s16)(-0x4000);
        angleState->flags = (u16)0;
        angleState->counter = 0x14;
        *(u8 *)((u8 *)obj + *(s16 *)((u8 *)obj + 0x22) * 2 + 0x19) = (u8)0;
        {
            s32 *p = &gMainObjTimerCallback;
            sub_080C31E4((u8 *)obj + 0x18, (u8 *)obj + 0x22, *p);
        }
    }
}
