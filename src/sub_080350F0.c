extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);

/* Script step: copy this entity's display-bank ids into its work object
 * (+0x4C from the entity, +0x48 a fixed value), clear then bump the step
 * phase byte, advance the script, and dispatch the new command's handler. */
void sub_080350F0(void *self)
{
    u32 *scriptTable;
    void *stepCursor;
    void *work = *((void **) (((s8 *) self) + 0x3C));
    *((s32 *) (((s8 *) work) + 0x4C)) = *((s32 *) (((s8 *) self) + 0x6C));
    *((s32 *) (((s8 *) work) + 0x48)) = 0x60000;
    *((u8 *) ((((s8 *) self) + (((s32) ((s16) ((u16 *) self)[0x11])) * 2)) + 0x19)) = 0;
    scriptTable = (u32 *) 0x08671BB0;
    stepCursor = ((s8 *) self) + 0x18;
    sub_080C31E4(stepCursor, ((s8 *) self) + 0x22, *scriptTable);
    *((u8 *) ((((s8 *) self) + (((s32) ((s16) ((u16 *) self)[0x11])) * 2)) + 0x19)) += 1;
    stepCursor += ((s32) ((s16) ((u16 *) self)[0x11])) * 2;
    sub_080C31E0(self, *((u32 *) (((u8 *) (*((u32 *) (((s8 *) self) + 0x14)))) + ((*((u8 *) stepCursor)) * 4))));
}
