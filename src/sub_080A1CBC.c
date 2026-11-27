extern void sub_08005E80(s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);

extern void *gScriptStepCallbacks;

/*
 * Script-step dispatcher. Copies self's coordinates into its target object and
 * clears a flag, then runs the step mode selected by self[0x7C]: a plain
 * callback, or a two-stage sequence that invokes a shared helper and a command
 * from the table at self+0x14.
 */
void sub_080A1CBC(u8 *entity)
{
    void *obj;
    void *ownerEnemy;
    u8 *self = entity;

    obj = *(void **)(self + 0x3C);
    {
        void *child = *(void **)(self + 0x28);
        ownerEnemy = *(void **)(child + 0x3C);
    }
    {
        void *enemyChild = *(void **)(obj + 0x28);
        ((u8 *)enemyChild)[1] = 0;
    }
    *(void **)(obj + 0x08) = *(void **)(self + 0x4C);
    *(void **)(obj + 0x0C) = *(void **)(self + 0x5C);

    switch (self[0x7C])
    {
    case 0:
    {
        if (1 & *(u16 *)ownerEnemy)
        {
            void *callback = *(void **)(self + 0x24);
            sub_080C31E0(self, callback);
        }
        break;
    }
    case 1:
    {
        s16 stepIndex;
        u8 *cmdPtr;
        void **callbackPtr;

        sub_08005E80(0x172);
        stepIndex = *(s16 *)(self + 0x22);
        *(u8 *)(self + stepIndex * 2 + 0x19) = 0;
        {
            callbackPtr = &gScriptStepCallbacks;
        }
        cmdPtr = self + 0x18;
        sub_080C31E8(cmdPtr, self + 0x22, 1, *callbackPtr);

        stepIndex = *(s16 *)(self + 0x22);
        *(u8 *)(self + stepIndex * 2 + 0x19) += 1;

        stepIndex = *(s16 *)(self + 0x22);
        cmdPtr += stepIndex * 2;
        obj = *(void **)(*(u32 *)(self + 0x14) + *cmdPtr * 4);
        sub_080C31E0(self, obj);
        break;
    }
    case 2:
    {
        s16 stepIndex;
        u8 *cmdPtr;
        void **callbackPtr;

        stepIndex = *(s16 *)(self + 0x22);
        *(u8 *)(self + stepIndex * 2 + 0x19) = 0;
        {
            callbackPtr = &gScriptStepCallbacks;
        }
        cmdPtr = self + 0x18;
        sub_080C31E8(cmdPtr, self + 0x22, 2, *callbackPtr);

        stepIndex = *(s16 *)(self + 0x22);
        *(u8 *)(self + stepIndex * 2 + 0x19) += 1;

        stepIndex = *(s16 *)(self + 0x22);
        cmdPtr += stepIndex * 2;
        obj = *(void **)(*(u32 *)(self + 0x14) + *cmdPtr * 4);
        sub_080C31E0(self, obj);
        break;
    }
    }
}
