extern void sub_08011EE8(void *, s32, s32);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_080C31E8(void *, void *, s32, u32);
extern u32 gMainObjTimerCallbacks[];
extern u32 gScriptStepCallbacks[];

/* Work state: +2 movement/collision flags; +0x10 is the horizontal velocity. */
struct WorkFlags { u8 pad[2]; u16 flags; };

/* Actor step: run the movement update, then choose the next script depending
 * on the collision flags. Flag bit 0 clears the horizontal velocity and runs
 * the normal script step; otherwise flag bit 2 runs script command 7 from the
 * alternate command table. */
void sub_0809980C(void *arg0)
{
    struct WorkFlags *work = (struct WorkFlags *)*(u8 **)((u8 *)arg0 + 0x3C);
    u32 flagBit;

    sub_08011EE8(work, 0x2D82, 0);
    flagBit = 1 & work->flags;
    if (flagBit)
    {
        *(u32 *)((u8 *)work + 0x10) = 0;
        *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22) * 2) + 0x19) = 0;
        {
            u32 *cmdTable = gMainObjTimerCallbacks;
            sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *cmdTable);
        }
    }
    else if (4 & work->flags)
    {
        *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22) * 2) + 0x19) = flagBit;
        {
            u32 *cmdTable = gScriptStepCallbacks;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 7, *cmdTable);
        }
    }
}
