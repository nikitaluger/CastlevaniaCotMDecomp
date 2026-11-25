void sub_08005E80(s32);
void sub_08011528(s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Animation tick: keep the actor's current animation playing; at script step
 * 0x4B play sound 0x186, clear the step and advance the script. */
void sub_080A3A90(void *arg0)
{
    s32 *stepTable;
    void *self;
    sub_08011528(*(s32 *)((u8 *)arg0 + 0x38), *(s32 *)((u8 *)arg0 + 0x3C) + 0x34);
    if (*(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) == 0x4B)
    {
        sub_08005E80(0x186);
        *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = 0;
        self = arg0;
        stepTable = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *stepTable);
    }
}
