extern void sub_080C31E4(void *, void *, u32);

/* When the task's +0x6C flag is set, set the attached sprite's two halfword
 * parameters to 0x400 and set its 0x40 flag bit, then clear this step's
 * progress byte and run the script interpreter for the current step. */
void sub_0809ED74(void *arg0)
{
    u8 *task = (u8 *)arg0;
    u8 *sprite = *((u8 **)(task + 0x38));
    s32 zero;
    int newFlags;
    u32 *scriptTable;

    if ((*((u8 *)(task + 0x6C))) == 0)
    {
        return;
    }
    zero = 0;
    {
        s32 value = 0x400;
        *((u16 *)(sprite + 4)) = value;
        *((u16 *)(sprite + 6)) = value;
    }
    newFlags = (*((u8 *)(sprite + 0x2A))) | 0x40;
    *((u8 *)(sprite + 0x2A)) = newFlags;
    *((u8 *)((task + ((*((s16 *)(task + 0x22))) * 2)) + 0x19)) = zero;
    scriptTable = (u32 *)0x08671BB0;
    sub_080C31E4(task + 0x18, task + 0x22, *scriptTable);
}
