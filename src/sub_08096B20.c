extern s32 sub_08096F00(void *);
extern void setObjectAnimationFrame(u32, u32, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u32 gScriptStepCallbacks;

struct ActorObj {
    u8 _0[0x14];
    u32 callbackTable;
    u8 _1[0x22 - 0x18];
    s16 scriptIndex;
    u8 _2[0x38 - 0x24];
    u32 soundId;
    u32 targetPtr;
};

struct Target {
    u8 _0[4];
    u32 flagArray;
    u8 _1[0x14 - 8];
    u16 status;
    u16 failFlag;
};

struct ScriptEntry {
    u8 _0[0x19];
    u8 state;
};

/* Check whether the actor's target is in range: on success play its sound and
 * set the status flag, otherwise set the failure flag; then fire the script's
 * callback and dispatch the next handler from the actor's table. */
void sub_08096B20(struct ActorObj *arg)
{
    u32 soundId;
    struct Target *target;
    u32 soundTarget;
    s32 inRange;

    soundId = arg->soundId;
    target = (struct Target *)arg->targetPtr;
    soundTarget = (u32)target + 0x18;
    inRange = sub_08096F00(arg);
    if (inRange == 1)
    {
        u8 *cbArgA;
        u8 *scriptPtr;
        u32 fn;
        u8 cmdIndex;
        u32 *pbd0;

        setObjectAnimationFrame(soundId, soundTarget, 7, 0);
        *(u8 *)(target->flagArray + 1) = 0;
        target->status = (u16)inRange;

        ((struct ScriptEntry *)((u8 *)arg + arg->scriptIndex * 2))->state = 0;
        pbd0 = &gScriptStepCallbacks;
        cbArgA = (u8 *)arg + 0x18;
        sub_080C31E8(cbArgA, (u8 *)arg + 0x22, 3, *pbd0);

        ((struct ScriptEntry *)((u8 *)arg + arg->scriptIndex * 2))->state++;
        scriptPtr = cbArgA + arg->scriptIndex * 2;
        cmdIndex = *scriptPtr;
        fn = *(u32 *)((u8 *)arg->callbackTable + cmdIndex * 4);
        sub_080C31E0(arg, fn);
    }
    else
    {
        u8 *cbArgA;
        u8 *scriptPtr;
        u32 fn;
        u8 cmdIndex;
        u32 *pbd0;
        s16 idx;

        target->failFlag = 1;
        idx = arg->scriptIndex;
        ((struct ScriptEntry *)((u8 *)arg + idx * 2))->state = 0;
        pbd0 = &gScriptStepCallbacks;
        cbArgA = (u8 *)arg + 0x18;
        sub_080C31E8(cbArgA, (u8 *)arg + 0x22, 1, *pbd0);

        ((struct ScriptEntry *)((u8 *)arg + arg->scriptIndex * 2))->state++;
        scriptPtr = cbArgA + arg->scriptIndex * 2;
        cmdIndex = *scriptPtr;
        fn = *(u32 *)((u8 *)arg->callbackTable + cmdIndex * 4);
        sub_080C31E0(arg, fn);
    }
}
