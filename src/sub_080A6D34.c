extern void sub_080A860C(void *, void *);
extern void sub_080A8940(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u32 D_08671BD0[];

/* Script-step callback: updates the control block shared with the companion,
 * then, when a trigger flag is set and its counter is zero, resets the current
 * script step and redirects the script to mode 3 or 8 depending on a flag. */
void sub_080A6D34(void *entity)
{
    void *companion = *(void **)((u8 *)entity + 0x38);
    void *scriptState = *(void **)((u8 *)entity + 0x3C);
    void *control = (u8 *)scriptState + 0x48;

    sub_080A860C(entity, control);
    sub_080A8940(companion, control);

    if (*(u8 *)((u8 *)scriptState + 0x120) != 0)
    {
        s32 triggerValue = *(s32 *)((u8 *)scriptState + 0x110);
        if (triggerValue == 0)
        {
            if (*(u8 *)((u8 *)entity + 0x4C) == 0)
            {
                s16 stepIndex = *(s16 *)((u8 *)entity + 0x22);
                *((u8 *)entity + stepIndex * 2 + 0x19) = 0;
                { u32 *pTable = D_08671BD0; sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 3, *pTable); }
            }
            else
            {
                s16 stepIndex = *(s16 *)((u8 *)entity + 0x22);
                *((u8 *)entity + stepIndex * 2 + 0x19) = 0;
                { u32 *pTable = D_08671BD0; sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 8, *pTable); }
            }
        }
    }
}
