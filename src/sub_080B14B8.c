s32 setPolarOffset(s32, s32, s32);
void sub_080B1960(s32, void *);
void sub_080C31E4(void *, void *, s32);

// AI step: update work against the linked object; once the step byte passes
// 0x18 and the linked object allows it, set the pose's motion value from the
// linked object's facing byte (-1 -> 0x4800, else 0x3800), zero the offset,
// start the motion via setPolarOffset, then reset the step byte and advance.
void sub_080B14B8(void *arg0)
{
    void *work;
    void *pose;
    void *subject;
    s32 *scriptTable;
    s32 facing, minusOne;

    work = *(void **)((s8 *)arg0 + 0x3C);
    pose = work;
    pose = (s8 *)pose + 0x48;
    subject = *(void **)((s8 *)arg0 + 0x4C);
    sub_080B1960((s32)work, subject);
    if (((u32) *(u8 *)((s8 *)(((*((s16 *)((s8 *)arg0 + 0x22))) * 2) + arg0) + 0x19)) > 0x18U)
    {
        if (*(u8 *)((s8 *)subject + 0x25) == 0)
        {
            facing = *(s8 *)((s8 *)subject + 0x35);
            minusOne = -1;
            if (facing == minusOne)
            {
                *(vu32 *)((s8 *)pose + 0x14) = 0x4800;
            }
            else
            {
                *(vu32 *)((s8 *)pose + 0x14) = 0x3800;
            }
            *(vu32 *)((s8 *)pose + 0x10) = 0;
            setPolarOffset((s32)work, *(vu32 *)((s8 *)pose + 0x14), 0);
            *(u8 *)((s8 *)(((*((s16 *)((s8 *)arg0 + 0x22))) * 2) + arg0) + 0x19) = 0;
            scriptTable = (s32 *)0x08671BB0;
            sub_080C31E4((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22, *scriptTable);
        }
    }
}
