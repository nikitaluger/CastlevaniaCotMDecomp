void setAnimationFrame(void *, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E0(void *, s32);

/* Copy the actor's position into its motion block, pick a direction from the
 * script flags, then reset the step, dispatch the follow-up script and run
 * the current command out of the jump table. */
void sub_08036848(void *arg0)
{
    void *source = *(void **)((u8 *)arg0 + 0x38);
    void *actor = *(void **)((u8 *)arg0 + 0x3C);
    void *status = (u8 *)actor + 0x34;
    void *motion = (u8 *)actor + 0x48;

    if (*(u8 *)((u8 *)arg0 + 0x70) != 0)
        setAnimationFrame(source, status, 0x12, 0);
    else
        setAnimationFrame(source, status, 0x0D, 0);

    *(s32 *)((u8 *)motion + 0x0C) = *(s32 *)((u8 *)actor + 0x08);
    *(s32 *)((u8 *)motion + 0x10) = *(s32 *)((u8 *)actor + 0x0C);

    if (*(u8 *)((u8 *)arg0 + 0x6C) != 0)
        *(s32 *)((u8 *)motion + 0x14) = 0x40000;
    else
        *(s32 *)((u8 *)motion + 0x14) = 0xFFFC0000;

    {
        s16 stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
        *((u8 *)arg0 + stepIndex * 2 + 0x19) = 0;
    }

    {
        s32 *dispatchPtr = (s32 *)0x08671BB0;
        void *scriptData = (u8 *)arg0 + 0x18;
        void *stepPtr = (u8 *)arg0 + 0x22;
        s32 dispatchValue = *dispatchPtr;
        sub_080C31E4(scriptData, stepPtr, dispatchValue);

        {
            s16 stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
            u8 *stepAddr = (u8 *)(stepIndex * 2);
            stepAddr = (u8 *)((u32)stepAddr + (u32)arg0);
            *(u8 *)(stepAddr + 0x19) = *(u8 *)(stepAddr + 0x19) + 1;
        }

        {
            s16 stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
            u8 *commandPtr = (u8 *)scriptData + stepIndex * 2;
            u8 command = *commandPtr;
            u32 jumpTable = *(u32 *)((u8 *)arg0 + 0x14);
            sub_080C31E0(arg0, *(s32 *)(jumpTable + command * 4));
        }
    }
}
